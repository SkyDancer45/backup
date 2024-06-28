#!/bin/bash

# Variables - Example values
resourceGroup="Vnet1"
vmName="Vnet1"
nicName="vnet1219_z1"
nsgName="Vnet1-nsg"
publicIpName="Vnet1-ip"
vnetName="Vnet1-vnet"
subnetName="default"
staticIpAddress="10.0.0.20"
newNicName="NewNIC"

# Step 1: Allocate a static IP to the VM's network interface
# Retrieve the NIC name associated with the VM
nicName=$(az vm show --resource-group $resourceGroup --name $vmName --query 'networkProfile.networkInterfaces[0].id' -o tsv | awk -F'/' '{print $NF}')

if [ -z "$nicName" ]; then
  echo "Network Interface not found for VM $vmName"
else
  # Check if the NIC and IP configuration exist
  nicExists=$(az network nic show --resource-group $resourceGroup --name $nicName --query id -o tsv)
  if [ -z "$nicExists" ]; then
    echo "Network Interface $nicName does not exist in resource group $resourceGroup"
  else
    # Try updating NIC with the specified static IP address
    echo "Updating NIC $nicName with static IP address $staticIpAddress..."
    az network nic ip-config update --resource-group $resourceGroup --nic-name $nicName --name ipconfig1 --private-ip-address $staticIpAddress --debug

    if [ $? -ne 0 ]; then
      echo "Failed to update NIC with static IP address. Check debug logs for details."
    else
      echo "Successfully updated NIC with static IP address."
    fi
  fi
fi

# Step 2: Create a Network Security Group (NSG)
az network nsg create --resource-group $resourceGroup --name $nsgName
if [ $? -ne 0 ]; then
  echo "Failed to create Network Security Group $nsgName."
else
  echo "Successfully created Network Security Group $nsgName."
fi

# Step 3: Create a Public IP
az network public-ip create --resource-group $resourceGroup --name $publicIpName --allocation-method Static
if [ $? -ne 0 ]; then
  echo "Failed to create Public IP $publicIpName."
else
  echo "Successfully created Public IP $publicIpName."
fi

# Step 4: Associate Public IP with the NIC
publicIpId=$(az network public-ip show --resource-group $resourceGroup --name $publicIpName --query id -o tsv)
az network nic ip-config update --resource-group $resourceGroup --nic-name $nicName --name ipconfig1 --public-ip-address $publicIpId
if [ $? -ne 0 ]; then
  echo "Failed to associate Public IP $publicIpName with NIC $nicName."
else
  echo "Successfully associated Public IP $publicIpName with NIC $nicName."
fi

# To De-associate Public IP from the NIC (uncomment the following line if needed)
# az network nic ip-config update --resource-group $resourceGroup --nic-name $nicName --name ipconfig1 --remove publicIpAddress

# Step 5: Create a Network Interface
# Retrieve the subnet ID
subnetId=$(az network vnet subnet show --resource-group $resourceGroup --vnet-name $vnetName --name $subnetName --query id -o tsv)

# Create NIC with the new NSG and public IP
az network nic create --resource-group $resourceGroup --name $newNicName --vnet-name $vnetName --subnet $subnetName --network-security-group $nsgName --public-ip-address $publicIpId
if [ $? -ne 0 ]; then
  echo "Failed to create Network Interface $newNicName."
else
  echo "Successfully created Network Interface $newNicName."
fi

echo "Script execution completed."

