#!/bin/bash

# Скрипт для установки загрузчика btt_downloader на терминалы AQSI CUBE

echo "Параметры: $@"


set -e

SSH_FINGERPRINT_CHECK_FIX="-o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o LogLevel=quiet"
SSH_USER_KEY_FILE="/var/tmp/user.key"
SSH_ROOT_KEY_FILE="/var/tmp/root.key"

#=================================================================================================

function error_and_exit() {
    echo -e "\n\e[31mОШИБКА: $1\e[0m"
    clean_keys
    exit 1
}

function usage() {
    echo -e "Установщик загрузчика на терминал AQSI CUBE"
    echo -e ""
    echo -e "$0 --ip=IP_ADDRESS --pkg=cube_btt_downloader_2.2.1.tar.gz"
    echo -e "\t-h --help"
    echo -e "\t--ip        - текущий IP адрес терминала"
    echo -e "\t--pkg       - архив с загрузчиком"
    exit 1
}

function make_ssh_commands_with_key() {
    SSH="ssh -i ${SSH_USER_KEY_FILE} ${SSH_FINGERPRINT_CHECK_FIX} user@${IP}"
    SSH_ROOT="ssh -i ${SSH_ROOT_KEY_FILE} ${SSH_FINGERPRINT_CHECK_FIX} root@${IP}"
    SCP="scp -v -i ${SSH_USER_KEY_FILE} ${SSH_FINGERPRINT_CHECK_FIX}"
    SCP_ROOT="scp -i ${SSH_ROOT_KEY_FILE} ${SSH_FINGERPRINT_CHECK_FIX}"

    echo "SSH=${SSH}"
    echo "SCP=${SCP}"
}

function create_keys() {
    if [ -e ${SSH_USER_KEY_FILE} ]; then
        rm ${SSH_USER_KEY_FILE}
    fi
    echo "-----BEGIN OPENSSH PRIVATE KEY-----
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
4Gz7E7Hpy08AAAALZ3NlQHBlbmd1aW4=
-----END OPENSSH PRIVATE KEY-----" > ${SSH_USER_KEY_FILE}
    chmod 600 ${SSH_USER_KEY_FILE}

    if [ -e ${SSH_ROOT_KEY_FILE} ]; then
        rm ${SSH_ROOT_KEY_FILE}
    fi
    echo "-----BEGIN OPENSSH PRIVATE KEY-----
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
XDS9XO3vltUAAAALZ3NlQHBlbmd1aW4=
-----END OPENSSH PRIVATE KEY-----" > ${SSH_ROOT_KEY_FILE}
    chmod 600 ${SSH_ROOT_KEY_FILE}
}

function clean_keys() {
    if [ -e ${SSH_USER_KEY_FILE} ]; then
        rm ${SSH_USER_KEY_FILE}
    fi
    if [ -e ${SSH_ROOT_KEY_FILE} ]; then
        rm ${SSH_ROOT_KEY_FILE}
    fi
}

#=================================================================================================

while [ "${1}" ]; do
  param=$(echo $1 | awk -F= '{print $1}')
  value=$(echo $1 | awk -F= '{print $2}')

  case ${param} in
  -h | --help)
    usage
    exit
    ;;
  --ip)
    IP=${value}
    if [ -z "${IP}" ]; then
      error_and_exit "IP не может быть пустым"
    fi
    ;;
  --pkg)
    PACKAGE_FILE=${value}
    if [ ! -f "${PACKAGE_FILE}" ]; then
      error_and_exit "файл ${PACKAGE_FILE} не найден!"
    fi
    ;;
  *)
    echo "Ошибка: неизвестный параметр \"${param}\""
    usage
    exit 1
    ;;
  esac
  shift
done

echo "IP = ${IP}"
echo "PACKAGE_FILE = ${PACKAGE_FILE}"

[ -z ${IP} ] || [ -z ${PACKAGE_FILE} ] && usage

# проверим что указанный адрес пингуется
ping -c 1 ${IP} || error_and_exit "адрес ${IP} не пингуется!"

create_keys
make_ssh_commands_with_key

TMP_DIR=/tmp
DOWNLOADER_DIR=/data/usr/home/btt_downloader

echo "Выключение сервиса btt_downloader..."
${SSH} systemctl --user stop btt_downloader.service || echo "Сервис btt_downloader не найден"
${SSH} systemctl --user disable btt_downloader.service || echo "Сервис btt_downloader не найден"
echo "OK"

echo "Удаление загрузчика и скрипта автозапуска"
${SSH} rm -rf /data/usr/home/.config/systemd/user/btt_downloader.service ${DOWNLOADER_DIR}
echo "OK"

echo "Копирование архива на терминал..."
${SCP} ${PACKAGE_FILE} user@${IP}:${TMP_DIR}/ || error_and_exit "Не удалось скопировать архив на терминал"
echo "OK"

echo "Копирование успешно завершено. Распаковка дистрибутива..."
echo "${SSH} tar -C ${TMP_DIR} -xf ${TMP_DIR}/${PACKAGE_FILE} --checkpoint=.100"

${SSH} tar -C ${TMP_DIR} -xf ${TMP_DIR}/${PACKAGE_FILE} --checkpoint=.100 || error_and_exit "Не удалось распаковать архив"
echo "OK"

echo "Изменяем владельца файла /data/aqsi-config.json на терминале"
${SSH_ROOT} "chown user /data/aqsi-config.json" && echo "Успешно!" || error_and_exit "не удалось изменить владельца"

echo "Изменяем владельца файла /data/etc/systemd/network.router.mode/20-wired.network на терминале"
${SSH_ROOT} "chown user /data/etc/systemd/network.router.mode/20-wired.network" && echo "Успешно!" || error_and_exit "не удалось изменить владельца"

echo "Изменяем владельца файла /data/etc/iptables.client.mode/iptables.rules на терминале"
${SSH_ROOT} "chown root:user /data/etc/iptables.client.mode/iptables.rules" && echo "Успешно!" || error_and_exit "не удалось изменить владельца"

echo "Изменяем владельца файла /data/etc/iptables.router.mode/iptables.rules на терминале"
${SSH_ROOT} "chown root:user /data/etc/iptables.router.mode/iptables.rules" && echo "Успешно!" || error_and_exit "не удалось изменить владельца"

PACKAGE_DIR=${TMP_DIR}/package

echo "Копируем загрузчик в рабочую директорию"
${SSH} cp -rf ${PACKAGE_DIR}/btt_downloader /data/usr/home/ || error_and_exit "не удалось скопировать загрузчик в рабочую директорию"
echo "OK"

${SSH} mkdir -p /data/usr/home/.config/systemd/user

echo "Включаем сервис btt_downloader.services"
${SSH} cp ${PACKAGE_DIR}/btt_downloader.service /data/usr/home/.config/systemd/user/ || error_and_exit "не удалось скопировать btt_downloader.service"
${SSH} systemctl --user enable btt_downloader.service || error_and_exit "не удалось активировать btt_downloader.service"
${SSH} cp -rf ${PACKAGE_DIR}/aqsi-config.json /data/ || error_and_exit "не удалось скопировать aqsi-config.json"
echo "OK"

${SSH} rm -rf ${PACKAGE_DIR} || error_and_exit "Не удалось удалить временные файлы"

$SSH "sync"
sleep 3
echo -e "\e[32mУстановка завершена, выполняется перезагрузка терминала\e[0m"
$SSH "sudo /sbin/reboot"

clean_keys
