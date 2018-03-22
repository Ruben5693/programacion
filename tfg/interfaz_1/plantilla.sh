name=$1
ram=$2
cpu=$3
storage=$4
ruta=$5

dd if=/dev/zero of=/var/lib/libvirt/images/$name.img bs=1024k count=$storage

virt-install --connect \
qemu:///system \
--name=$name \
--virt-type=kvm \
--boot cdrom,hd \
--network=default,model=virtio \
--disk path=/var/lib/libvirt/images/$name.img,size=10,format=img,bus=virtio,cache=none \
--memory=$ram \
--vcpu=$cpu  \
--cdrom=$ruta 