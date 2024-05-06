FILE_MAC="$3/mac_address_$2.txt"

rm $FILE_MAC
ping -c1 $1
ping -c1 $1
ping -c1 $1


# /Users/polzovatel/work/aqsi_proj/TerminalInstallerApp/installerAppForMac_0.1/installerApp/build/mac_address.txt
arp $1 | grep $1 | awk '{print $4}' >> $FILE_MAC