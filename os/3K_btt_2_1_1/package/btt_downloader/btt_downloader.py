# -*- coding: utf-8 -*-
import json
import sys
import time
from urllib.parse import urlparse
import hashlib
from datetime import datetime
import os
import subprocess
from shutil import rmtree
import tarfile
import logging.handlers
import ssl
from http import client
import argparse
import binascii
from http.server import HTTPServer, BaseHTTPRequestHandler
from threading import Thread
import re

version = "2.2.1"

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
SETTINGS_FILE = os.path.join(CURRENT_DIR, "settings.json")
CONFIGURE_NETWORK_SCRIPT = os.path.join(CURRENT_DIR, "configure_network.sh")
PACKAGE_FILE = os.path.join(CURRENT_DIR, "distrib.tar.gz")
REQUEST_RETRIES_COUNT = 5
APPLET_DATA_CHUNK_SIZE = 250
APPLET_ID = "4441544153544F52414745"
MASTER_IP = "192.168.1.10"
PORT = 8100
PLATFORMS = {
    "aqsi_cube": "cube",
    "vendotek_full": "vendotek"
}

SLAVES_UPDATE_STATUS = {}
PACKAGE_DATA = None


def get_package_data():
    global PACKAGE_DATA
    if not PACKAGE_DATA:
        with open(PACKAGE_FILE, "rb") as file:
            logger.info("Cache package data")
            PACKAGE_DATA = file.read()
    else:
        logger.info("Cache of the package data already exists")
    return PACKAGE_DATA


class CustomHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        try:
            global SLAVES_UPDATE_STATUS
            if os.path.isfile(PACKAGE_FILE):
                self.send_response(200)
                self.end_headers()
                if self.path == "/get_package":
                    self.wfile.write(get_package_data())
                elif re.match(r"/slave\d/success", self.path):
                    role = self.path.split("/")[1]
                    SLAVES_UPDATE_STATUS[role] = True
            else:
                self.send_response(404)
                self.end_headers()
        except Exception as e:
            logger.error(str(e))

    def log_message(self, format, *args):
        logger.info("Got request from %s, status: %s" % (self.address_string(), list(args)))


class Server:
    def __init__(self):
        cmd = "busctl call org.hwkeeper /client org.hwkeeper.Firewall OpenPort uu 2 %s" % PORT
        logger.info("Open port %s with command: %s" % (PORT, cmd))
        result = subprocess.run(args=[cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True).stdout.decode("utf-8").strip()
        logger.info("Result: %s" % result)

        logger.info("Starting http server")
        self.httpd = HTTPServer(("0.0.0.0", PORT), CustomHTTPRequestHandler)
        self.thread = Thread(target=self.httpd.serve_forever, daemon=True)
        self.thread.start()
        logger.info("Server started")

    def __del__(self):
        logger.info("Server stopped")


class IntelliReader:
    def __init__(self, platform):
        self.platform = platform
        self.ird_dir = os.path.join(CURRENT_DIR, "ird")
        logger.info("Starting ird from %s" % self.ird_dir)
        self.ird_process = subprocess.Popen(["./ird"], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        logger.info("Ird was started")

    def start_apdu_session(self):
        cmd = "./irc --cmd exchangeApduSessionIntro; echo $?"
        result = subprocess.run([cmd], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                shell=True).stdout.decode("utf-8").strip()
        logger.info("exchangeApduSessionIntro result: %s" % result)

    def end_apdu_session(self):
        cmd = "./irc --cmd exchangeApduSessionOutro; echo $?"
        result = subprocess.run([cmd], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                shell=True).stdout.decode("utf-8").strip()
        logger.info("exchangeApduSessionOutro result: %s" % result)

    def send_apdu(self, apdu):
        cmd = "./irc --cmd exchangeApdu --apdu=%s" % apdu
        logger.debug("apdu: %s" % apdu)
        result = subprocess.run([cmd], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                shell=True).stdout.decode("utf-8").strip()
        sw = result[-4:]
        data = result[:-4]
        logger.debug("sw: %s, data: %s" % (sw, data))
        if sw != "9000":
            logger.error("Bad apdu response. Apdu: %s, sw: %s" % (apdu, sw))
            return False
        return data

    def show_screen_message(self, message, led_state=0):
        cmd = "./irc --cmd showGuiColoredMessage --ledState %s --msg \"%s\" --timeout 0" % (led_state, message)
        if self.platform == PLATFORMS["aqsi_cube"]:
            cmd = "./irc --cmd setGuiState --guiState 12 --ledState %s --guiStateTextWithSingleButtonTxt \"%s\"" % (led_state, message)
        subprocess.run([cmd], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

    def beep(self):
        cmd = "./irc --cmd playSound --soundVariant=0"
        subprocess.run([cmd], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

    def wait_card(self):
        cmd = "./irc --cmd WaitCard --timeout 0; echo $?"
        logger.info("wait_card cmd: %s" % cmd)
        result = subprocess.run([cmd], cwd=self.ird_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                shell=True).stdout.decode("utf-8").strip()
        logger.info("wait_card result: %s" % result)
        if result != "0":
            return False
        return True

    def __del__(self):
        logger.info("Killing ird (pid=%s)" % self.ird_process.pid)
        self.ird_process.kill()


def hex_to_int(s):
    """
    input: FF
    output: 255
    """
    return int(s, 16)


def int_to_hex(data):
    """
    input: 11
    output: 0B
    """
    hex_str = hex(data)[2:]
    while len(hex_str) % 2 != 0:
        hex_str = "0" + hex_str
    return hex_str


def split_str_by_symbols(s, n=2):
    """
    input: '0123456789ABCDEF'
    output: ['01', '23', '45', '67', '89', 'AB', 'CD', 'EF']
    """
    return [s[i:i + n] for i in range(0, len(s), n)]


def md5sum(file):
    hash_md5 = hashlib.md5()
    with open(file, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()


def calc_crc32(data):
    crc32 = hex(
        binascii.crc32(
            binascii.a2b_hex(
                bytearray(data, encoding="utf-8"))))[2:]
    while len(crc32) != 8:
        crc32 = "0" + crc32
    return crc32.upper()


def parse_card_data(card_data):
    params_str = bytearray.fromhex(card_data[4:-8]).decode()
    params = dict(map(lambda item: item.split("=", 1), params_str.split(",")))

    role = int(params["ROLE"])
    if role == 0:
        params["ROLE"] = "master"
    else:
        params["ROLE"] = "slave%s" % role

    return params


def read_card(ird: IntelliReader):
    if not ird.wait_card():
        return False

    ird.start_apdu_session()

    fci = ird.send_apdu("00A4040006F75246544301")
    if not fci:
        return False

    applet_id = fci[4:26]
    if applet_id != APPLET_ID:
        logger.warning("Unknown applet: %s" % applet_id)
        return False

    logger.info("Found card with DataStorage applet")

    read_data_cmd = "00B0"
    data_len_hex = ird.send_apdu(read_data_cmd + "000002")
    if not data_len_hex:
        return False
    data_len_int = 256 * hex_to_int(data_len_hex[:2]) + hex_to_int(data_len_hex[2:4])
    logger.info("Blob length: %s bytes" % data_len_int)

    blocks = data_len_int // APPLET_DATA_CHUNK_SIZE + 1
    last_block_size = data_len_int % APPLET_DATA_CHUNK_SIZE

    data = ""
    p1 = 0
    p2 = 0
    read_len = 0

    for i in range(0, blocks):
        le = last_block_size if i == blocks - 1 else APPLET_DATA_CHUNK_SIZE
        cmd = read_data_cmd + int_to_hex(p1) + int_to_hex(p2) + int_to_hex(le)
        data_chunk = ird.send_apdu(cmd)
        if not data_chunk:
            return False
        data += data_chunk
        read_len += le
        p1 = read_len // 256
        p2 = read_len % 256

    ird.end_apdu_session()
    return data


def send_request(url, ssl_context=None):
    conn = None
    try:
        parsed_url = urlparse(url)
        logger.info("Parsed url host: %s, port: %s, path: %s" % (parsed_url.hostname, parsed_url.port, parsed_url.path))
        if ssl_context:
            conn = client.HTTPSConnection(host=parsed_url.hostname, port=parsed_url.port, context=ssl_context, timeout=15)
        else:
            conn = client.HTTPConnection(host=parsed_url.hostname, port=parsed_url.port, timeout=15)
        conn.request("GET", url=parsed_url.path)
        resp = conn.getresponse()
        logger.info("Response status: %s %s" % (resp.status, resp.reason))
        logger.info("Headers: %s" % resp.getheaders())
        data = None
        if resp.status == 200:
            data = resp.read()
        return data, resp.status
    except Exception as e:
        logger.error(str(e))
        return False, str(e)
    finally:
        if conn:
            conn.close()


def write_to_file(file, data):
    with open(file, "w") as f:
        f.write(data)


def remove_directory_if_exists(dir_name):
    if os.path.isdir(dir_name):
        logger.info("Directory %s exist, deleting..." % dir_name)
        rmtree(dir_name)


def remove_file_if_exists(filename):
    if os.path.isfile(filename):
        logger.info("File %s exist, deleting..." % filename)
        os.remove(filename)


if __name__ == '__main__':

    parser = argparse.ArgumentParser(usage="btt_downloader.py -p PLATFORM")
    parser.add_argument("-p", "--platform", required=True, help="Platform of the terminal")
    parser.add_argument("-l", "--log_level", required=False, default="info", help="Log level (=info): info | debug")
    args = parser.parse_args()
    device_platform = args.platform
    log_level = args.log_level

    # configure logger
    logger = logging.getLogger(__name__)
    formatter = logging.Formatter("btt_downloader: %(message)s")
    if log_level == "debug":
        logger.setLevel(logging.DEBUG)
    else:
        logger.setLevel(logging.INFO)
    handler = logging.handlers.SysLogHandler(address="/dev/log")
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    logger.info("Start btt_downloader %s, current platform: %s" % (version, device_platform))

    if device_platform == PLATFORMS["aqsi_cube"]:
        tmp_dir = "/data/usr/home/downloader_tmp/"
        utt_work_dir = "/data/usr/home/utt/"
        reboot_cmd = "sync && sleep 1 && sudo /sbin/reboot"
    elif device_platform == PLATFORMS["vendotek_full"]:
        tmp_dir = "/data/downloader_tmp/"
        utt_work_dir = "/home/root/utt/"
        reboot_cmd = "sync && sleep 1 && /sbin/reboot"
    else:
        logger.error("Unknown platform: %s, exit" % device_platform)
        sys.exit(0)

    ird = IntelliReader(device_platform)

    current_ip = subprocess.run(
        args=["ifconfig | grep inet | awk '{print $2}' | head -1"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        shell=True
    ).stdout.decode("utf-8").strip()
    current_ip = re.findall(r"\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$", current_ip)[0]
    if not current_ip:
        current_ip = "unknown"

    if not os.path.exists(SETTINGS_FILE):

        # проверка наличия установленного ПО
        if os.path.exists(utt_work_dir):
            logger.info("Found UTT working directory %s" % utt_work_dir)
            waitcard_timeout = 5
        else:
            logger.info("UTT working directory %s not found" % utt_work_dir)
            waitcard_timeout = sys.maxsize

        ird.show_screen_message("IP: %s\n\nWAIT FOR DATASTORAGE CARD..." % current_ip)

        start_time = datetime.now()
        card_data = ""

        logger.info("Wait card for %s sec" % waitcard_timeout)
        # ожидание загрузочной карты. Если уже установлено ПО - ждём 5 сек, если нет - то ждём бесконечно
        while (datetime.now() - start_time).seconds < waitcard_timeout:
            card_data = read_card(ird)
            if card_data:
                ird.beep()
                expected_crc32 = card_data[-8:]
                actual_crc32 = calc_crc32(card_data[:-8])
                if actual_crc32 != expected_crc32:
                    logger.error("Wrong crc32. Actual: %s, expected: %s" % (actual_crc32, expected_crc32))
                    ird.show_screen_message(message="ERROR: WRONG CRC32", led_state=3)
                    time.sleep(2)
                    ird.show_screen_message("IP: %s\n\nWAIT FOR DATASTORAGE CARD..." % current_ip)
                else:
                    break
            time.sleep(0.2)

        if not card_data:
            logger.info("Wait card timeout expired, exit")
            sys.exit(0)

        ird.show_screen_message("CONFIGURE NETWORK SETTINGS...")
        config_params = parse_card_data(card_data)
        logger.info("Save config to the file %s" % SETTINGS_FILE)
        write_to_file(SETTINGS_FILE, json.dumps(config_params, indent=4))

        arguments = ""
        for param, value in config_params.items():
            if param not in ["CA_CERT", "CLIENT_CERT", "CLIENT_KEY"]:
                if value:
                    arguments += " --" + param + "=" + value

        command = CONFIGURE_NETWORK_SCRIPT + " " + arguments
        logger.info("Run configuring script: %s" % command)
        result = subprocess.run([command], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        logger.info("Script return code: %s" % result.returncode)

        if result.returncode != 0:
            ird.show_screen_message(message="ERROR: FAILED TO SET NETWORK SETTINGS", led_state=3)
            sys.exit(0)

        ird.show_screen_message("NETWORK SETUP COMPLETED.\nSYSTEM WILL REBOOT", led_state=2)
        logger.info("Reboot system to accept network settings, cmd: %s" % reboot_cmd)
        os.system(reboot_cmd)
        sys.exit(0)

    else:

        logger.info("Config already exist, read from file %s" % SETTINGS_FILE)
        with open(SETTINGS_FILE, "r") as f:
            config_params = json.loads(f.read())

    logger.info("Dump config params:\n")
    for k, v in config_params.items():
        if k not in ["CA_CERT", "CLIENT_CERT", "CLIENT_KEY"]:
            logger.info("%s: %s" % (k, v))

    certs_dir = os.path.join(CURRENT_DIR, "cert")
    if not os.path.exists(certs_dir):
        logger.info("Cert directory %s not found. Creating..." % certs_dir)
        os.mkdir(certs_dir)

    ca_cert_file = os.path.join(certs_dir, "ca.crt")
    client_cert_file = os.path.join(certs_dir, "client.crt")
    client_key_file = os.path.join(certs_dir, "client.key")

    ca_cert = config_params.pop("CA_CERT")
    client_cert = config_params.pop("CLIENT_CERT")
    client_key = config_params.pop("CLIENT_KEY")

    write_to_file(ca_cert_file, ca_cert)
    write_to_file(client_cert_file, client_cert)
    write_to_file(client_key_file, client_key)

    remove_file_if_exists(SETTINGS_FILE)

    term_info = "Role: %s\nIP: %s\n\n" % (config_params["ROLE"], current_ip)

    if config_params["ROLE"].startswith("slave"):
        logger.info("Do configure as %s" % config_params["ROLE"])
        logger.info("Downloading package to %s" % PACKAGE_FILE)
        attempt_count = 1
        pkg = None
        while True:
            ird.show_screen_message(term_info + "LOADING PACKAGE... ATTEMPT #%s" % attempt_count)
            pkg, status = send_request("http://%s:%s/get_package" % (MASTER_IP, PORT))
            if pkg:
                break
            ird.show_screen_message(message="ERROR: LOADING PACKAGE... ATTEMPT #%s, status: %s" % (attempt_count, status), led_state=3)
            time.sleep(5)
            attempt_count += 1

        if not pkg:
            ird.show_screen_message(message="ERROR: FAILED TO GET PACKAGE", led_state=3)
            logger.error("Failed to download package")
            sys.exit(0)

        with open(PACKAGE_FILE, "wb") as f:
            f.write(pkg)

        logger.info("Package was downloaded successfully")

        data, res = send_request("http://%s:%s/%s/success" % (MASTER_IP, PORT, config_params["ROLE"]))

    elif config_params["ROLE"] == "master":
        ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS)
        ssl_context.verify_mode = ssl.CERT_REQUIRED
        ssl_context.load_verify_locations(cafile=ca_cert_file)
        ssl_context.load_cert_chain(certfile=client_cert_file, keyfile=client_key_file)

        software_url = config_params.pop("SOFT_URL")

        # скачиваем с сервера файл software.json
        setup_info = None
        for i in range(1, REQUEST_RETRIES_COUNT + 1):
            ird.show_screen_message(term_info + "LOADING SOFTWARE.JSON... ATTEMPT #%s" % i)
            setup_info, status = send_request(software_url, ssl_context)
            if setup_info:
                logger.info("Get setup info: %s" % setup_info)
                break
            ird.show_screen_message(message="ERROR: LOADING SOFTWARE.JSON... ATTEMPT #%s, status: %s" % (i, status),
                                    led_state=3)
            time.sleep(5)

        if not setup_info:
            ird.show_screen_message(message="ERROR: FAILED TO GET SOFTWARE.JSON", led_state=3)
            logger.error("Can't get software.json, exit")
            sys.exit(0)

        try:
            setup_info = json.loads(setup_info.decode("utf-8").replace("\r\n", ""))
        except json.JSONDecodeError as e:
            ird.show_screen_message(message="ERROR: INVALID FORMAT OF SOFTWARE.JSON", led_state=3)
            logger.error("Setup info is invalid, got json parsing error: %s" % str(e))
            sys.exit(0)

        software_info = None
        for item in setup_info["SOFTWARE_SETUP"]:
            if item["NAME"] == device_platform:
                logger.info("Found software: %s" % item)
                software_info = item
                break

        if not software_info:
            logger.info("Software not found")
            sys.exit(0)

        # удалили и создали заново временную директорию
        remove_directory_if_exists(tmp_dir)
        logger.info("Create temp directory: %s" % tmp_dir)
        os.mkdir(tmp_dir)

        pkg = None
        logger.info("Downloading package to %s" % PACKAGE_FILE)
        for i in range(1, REQUEST_RETRIES_COUNT + 1):
            ird.show_screen_message(term_info + "LOADING PACKAGE... ATTEMPT #%s" % i)
            pkg, status = send_request(software_info["DOWNLOAD_URL"], ssl_context)
            if pkg:
                break
            ird.show_screen_message(message="ERROR: LOADING PACKAGE... ATTEMPT #%s, status: %s" % (i, status), led_state=3)
            time.sleep(5)

        if not pkg:
            ird.show_screen_message(message="ERROR: FAILED TO GET PACKAGE", led_state=3)
            logger.error("Failed to download package")
            sys.exit(0)

        with open(PACKAGE_FILE, "wb") as f:
            f.write(pkg)

        del pkg
        logger.info("Package was downloaded successfully")

        expected_md5 = software_info["MD5"]
        actual_md5 = md5sum(PACKAGE_FILE)
        if expected_md5 != actual_md5:
            ird.show_screen_message(message="ERROR: INVALID MD5", led_state=3)
            logger.error("Check md5 failed. Expected_md5=%s, actual_md5=%s" % (expected_md5, actual_md5))
            sys.exit(0)
        logger.info("Checking md5 = true")

        if device_platform == PLATFORMS["aqsi_cube"]:
            slaves_count = int(config_params["SLAVES_COUNT"])
            if slaves_count > 0:
                get_package_data()
                for i in range(1, slaves_count + 1):
                    SLAVES_UPDATE_STATUS["slave%s" % i] = False
                logger.info("Slaves update status: %s" % SLAVES_UPDATE_STATUS)
                s = Server()

                while True:
                    if False not in list(SLAVES_UPDATE_STATUS.values()):
                        logger.info("All slaves got package")
                        del s
                        del PACKAGE_DATA
                        break
                    update_msg = "WAITING FOR UPDATE SLAVES\n"
                    for key in SLAVES_UPDATE_STATUS.keys():
                        update_msg += "\n%s status: %s" % (key, SLAVES_UPDATE_STATUS[key])
                    ird.show_screen_message(message=update_msg)
                logger.info("Slaves update status: %s" % SLAVES_UPDATE_STATUS)

    success_install = False
    try:
        ird.show_screen_message(term_info + "EXTRACT PACKAGE...")
        logger.info("Extract %s to %s" % (PACKAGE_FILE, tmp_dir))
        tar_file = tarfile.open(name=PACKAGE_FILE)
        tar_file.extractall(path=tmp_dir)
        tar_file.close()
        logger.info("Extract done")

        ird.show_screen_message(term_info + "CONFIGURE DEVICE...")
        logger.info("Configuring device as %s. Router_flag=%s, srd_enabled=%s" % (config_params["ROLE"], config_params["ROUTER_FLAG"], config_params["SRD"]))
        install_script = os.path.join(tmp_dir, "package", "tk-install.sh")

        arguments = "--CERT_DIR=" + certs_dir
        for item, value in config_params.items():
            if value:
                arguments += " --" + item + "=" + value

        command = install_script + " " + arguments
        logger.info("Run install script: %s" % command)
        result = subprocess.run([command], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        logger.info("Script return code: %s" % result.returncode)
        logger.debug("Script result: %s" % str(result))
        if result.returncode != 0:
            raise Exception("Setup script return error code: %s" % result.returncode)
        success_install = True
        logger.info("Setup completed successfully")
        ird.show_screen_message(message=term_info + "SETUP COMPLETED SUCCESSFULLY.\nSYSTEM WILL REBOOT", led_state=2)
    except Exception as e:
        logger.error(str(e))
        ird.show_screen_message(message="ERROR: FAILED TO SETUP SOFTWARE", led_state=3)
        sys.exit(0)
    finally:
        remove_directory_if_exists(tmp_dir)
        remove_file_if_exists(SETTINGS_FILE)
        remove_file_if_exists(PACKAGE_FILE)
        if success_install:
            logger.info("Reboot system")
            os.system(reboot_cmd)
