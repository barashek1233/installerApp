#!/bin/sh

set -e

LOG_FILE="/data/usr/home/configure_network.log"
CURRENT_DIR=$(dirname $(readlink -f $0))
CUBE_ROUTER="disabled"
AQSI_CONFIG_FILE="/data/aqsi-config.json"

if [ -f ${LOG_FILE} ]; then
    mv ${LOG_FILE} ${LOG_FILE}.prev
fi

# $1 - text to log and show
log_and_show_info() {
    echo $1
    echo "$(date '+%d/%m/%Y %H:%M:%S') $1" >> ${LOG_FILE}
}

error_and_exit() {
    echo "ERROR: $1"
    echo "$(date '+%d/%m/%Y %H:%M:%S') ERROR: $1" >> ${LOG_FILE}
    exit 1
}

create_aqsi_config() {
    log_and_show_info "Create aqsi-config.json for role=${ROLE}"
    echo "{
        \"DefaultAppService\": \"org.aqsi.Vend\",
        \"Model\": 1234,
        \"CheckReport\": true,
        \"SalesStatisticSource\": 0,
        \"EvaDtsReportSchedule\": {
            \"Weekday\": [
                \"mon\",
                \"tue\",
                \"wed\",
                \"thu\",
                \"fri\",
                \"sat\",
                \"sun\"
            ],
            \"TimeFrom\": \"00:00\",
            \"TimeTo\": \"00:00\",
            \"Period\": 2
        },
        \"BusInactiveTimeout\": 180,
        \"MainMode\": 1,
        \"ClientEnable\": 0,
        \"CashlessLevel\": 1,
        \"CashlessAddress\": 16,
        \"ScaleFactor\": 1,
        \"DecimalPlacesCash\": 2,
        \"DecimalPlacesCashless\": 2,
        \"VMCAuditPortEnable\": false,
        \"VMCAuditPort\": 1,
        \"VMCAuditBaudRate\": 9600,
        \"VMCAuditProtocol\": 0,
        \"AcquiringShiftCloseTime\": \"12:00\",
        \"AcquiringShiftClosePeriod\": 1,
        \"CCAuditPortEnable\": false,
        \"PosMode\": 0,
        \"PosPort\": 0,
        \"NtpDisable\": true,
        \"DeviceNonGuiModeEnabled\": true,
        \"JpayDisable\": true,
        \"DoNotStopDm\": 1," > ${AQSI_CONFIG_FILE}

    if [ ${ROLE} == "master" ] && [ ${CUBE_ROUTER} == "enabled" ]; then
        echo "\"CellularRouterModeEnable\": true,
            \"CellularAPN\": \"${APN}\",
            \"CellularUsername\": \"${APN_USER}\",
            \"CellularPassword\": \"${APN_PASS}\",
            \"CellularAuthMethod\": \"chap\"" >> ${AQSI_CONFIG_FILE}
    else
        echo "\"CellularRouterModeEnable\": false" >> ${AQSI_CONFIG_FILE}
    fi

    echo "}" >> ${AQSI_CONFIG_FILE}
}

configure_network() {
    log_and_show_info "Configuring network..."
    CONNMAN_WIRED=$(connmanctl services | grep "Wired" | awk '{print $3}') || error_and_exit "Can't get connman wired interface"
    if [ "$ROLE" == "master" ]; then
        IP=192.168.1.10
    else
        SLAVE_NUM=$(echo "$ROLE" | awk -F'[^0-9]*' '$0=$2')
        IP=192.168.1.$(($SLAVE_NUM+10))
    fi
    connmanctl config ${CONNMAN_WIRED} --ipv4 manual ${IP} 255.255.255.0 ${GATEWAY} nameservers ${DNS} &
    sleep 10
    log_and_show_info "IP was changed to ${IP}"
}

remove_directory() {
    local directory=$1
    if [ -d ${directory} ]; then
        log_and_show_info "Removing ${directory}..."
        rm -rf ${directory}
    fi
}

while [ ${1} ]; do
  param=$(echo $1 | awk -F= '{print $1}')
  value=$(echo $1 | awk -F= '{print $2}')

  case ${param} in
  --ROLE)
    ROLE=${value}
    if [ ${ROLE} != "master" ] && ! [[ ${ROLE} =~ ^slave[1-9]$ ]]; then
      log_and_show_info "Error: unknown terminal role: ${ROLE}"
      exit 1
    fi
    ;;
  --APN)
    APN=${value}
    ;;
  --APN_USER)
    APN_USER=${value}
    ;;
  --APN_PASS)
    APN_PASS=${value}
    ;;
  --ROUTER_FLAG)
    if [ ${value} == "0" ]; then
      CUBE_ROUTER="enabled"
    fi
    ;;
  *)
    log_and_show_info "Warning: unknown param: ${param}"
    ;;
  esac
  shift
done

log_and_show_info "########################################"
log_and_show_info "Dump all params:"
log_and_show_info "ROLE: ${ROLE}"
log_and_show_info "APN: ${APN}"
log_and_show_info "APN_USER: ${APN_USER}"
log_and_show_info "APN_PASS: ${APN_PASS}"
log_and_show_info "CUBE_ROUTER: ${CUBE_ROUTER}"
log_and_show_info "########################################"

create_aqsi_config

GATEWAY=192.168.1.1
DNS=192.168.1.1
configure_network

if [ ${CUBE_ROUTER} == "enabled" ]; then

    if [ ${ROLE} == "master" ]; then
        log_and_show_info "Add settings to file ${WIRED_NETWORK_FILE}"
        WIRED_NETWORK_FILE="/data/etc/systemd/network.router.mode/20-wired.network"
        echo "[Match]" > ${WIRED_NETWORK_FILE}
        echo "Name=eth0" >> ${WIRED_NETWORK_FILE}
        echo "[Network]" >> ${WIRED_NETWORK_FILE}
        echo "Address=192.168.1.10/24" >> ${WIRED_NETWORK_FILE}
    else
        GATEWAY=192.168.1.10
        DNS=8.8.8.8
        configure_network
    fi
fi

log_and_show_info "Configure network settings done"

exit 0
