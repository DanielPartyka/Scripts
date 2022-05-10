source admin-openrc.sh
source openrc admin
echo "Welcome, your machines are listed below"
openstack server list

echo "1. Add machine"
echo "2. Delete machine" 
echo "3. Stop machine"
echo "4. Resume machine"
echo "5. Leave script"
read -p 'Choice: ' choice

if [ $choice = 1 ]; then
	read -p 'Nazwa maszyny=' servername
	openstack server create $servername --flavor ds1G --image obraz --nic net-id=<network_id> --security-group <security_group_id> --key-name <ssh_key_name>
	echo "Created machine $servername" 
elif [ $choice = 2 ]; then
	read -p 'Machine id:= ' id
	openstack server delete $id
	echo "Deleted machine id=$id"
elif [ $choice = 3 ]; then
	read -p 'Id maszyny:= ' id
	openstack server stop $id
	echo "Stopped machine id=$id" 
elif [ $choice = 4 ]; then
        openstack server start $id
	read -p 'Id maszyny:= ' id
	echo "Machine started o id=$id" 
else
	exit 0
fi 
