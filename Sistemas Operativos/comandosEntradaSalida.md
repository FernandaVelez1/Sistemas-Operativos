# SISTEMAS OPERATIVOS
    Alumna: FERNANDA ELIZABETH VÉLEZ ALEJANDRE (22121321)

## COMANDOS DE ENTRADA Y SALIDA, DISCOS Y ARCHIVOS

### EJERCICIO 1: MONTAR Y DESMONTAR DISCOS
En este ejercicio, se aprenderio a montar y desmontar una memoria USB en una máquina virtual. Se utiliza el comando lsblk para identificar el dispositivo y mount para asociarlo a un directorio específico. Luego, se copio un archivo hacia la memoria y se desmontó correctamente con umount.

```c
lizzie@Lizzie-VirtualBox:~$ df -h
S.ficheros     Tamaño Usados  Disp Uso% Montado en
tmpfs            1,6G    11M  1,6G   1% /run
/dev/nvme0n1p5    23G    18G  4,3G  81% /
tmpfs            7,8G    92M  7,7G   2% /dev/shm
tmpfs            5,0M    12K  5,0M   1% /run/lock
efivarfs         192K    91K   97K  49% /sys/firmware/efi/efivars
/dev/nvme0n1p1    96M    32M   65M  33% /boot/efi
tmpfs            1,6G   148K  1,6G   1% /run/user/1000
/dev/nvme0n1p3    96G    54G   43G  56% /media/lizzie/BAEED6DCEED68FCD
/dev/sda1         95G    99M   95G   1% /media/lizzie/Disco Duro
/dev/sda3        822G    12G  769G   2% /media/lizzie/8a77c684-db16-4591-8afa-ab23489a2935
/dev/sdb1        255M   8,5M  247M   4% /mnt/usb
/dev/sdb3        512M    24K  512M   1% /media/lizzie/62FC-C68B
```

Al final del ejercicio, el sistema reconocio y monto correctamente la memoria USB, permitiéndole copiar archivos hacia ella. Tras desmontar, la memoria quedo liberada y segura para su extracción.

```c
lizzie@Lizzie-VirtualBox:~$ nano archivo.txt
lizzie@Lizzie-VirtualBox:~$ cp archivo.txt /mnt/usb/
lizzie@Lizzie-VirtualBox:~$ sudo umount /mnt/usb
```

---
---
### EJERCICIO 2: REDIRECCIÓN DE ENTRADA Y SALIDA

- Se ejecutó el comando **ls -l** para listar los archivos del directorio actual en formato largo y se redirigió la salida al archivo **listado.txt**.

- Se utilizó **cat** para visualizar el contenido del archivo **listado.txt** en la terminal.
```c
total 88
-rw-rw-r-- 1 lizzie lizzie     0 dic 15 18:14 archivo.txt
drwxr-xr-x 2 lizzie lizzie  4096 dic  2 23:24 Descargas
-rwxrwxr-x 1 lizzie lizzie  1052 dic 15 15:22 dispositivos.sh
drwxr-xr-x 4 lizzie lizzie  4096 dic 15 02:07 Documentos
drwxr-xr-x 2 lizzie lizzie  4096 dic 15 17:04 Escritorio
drwxr-xr-x 3 lizzie lizzie  4096 nov 30 19:50 Imágenes
-rw-rw-r-- 1 lizzie lizzie     0 dic 18 18:53 listado.txt
drwxr-xr-x 2 lizzie lizzie  4096 nov  1 18:26 Música
drwxr-xr-x 2 lizzie lizzie  4096 nov  1 18:26 Público
```
- Se usó el comando **date** para obtener la fecha y hora actuales, añadiendo la salida al final del archivo **listado.txt** con la redirección **>>**.
- Se mostró de nuevo el contenido de **listado.txt**, ahora incluyendo la lista de archivos y la fecha actual.
```c
total 88
-rw-rw-r-- 1 lizzie lizzie     0 dic 15 18:14 archivo.txt
drwxr-xr-x 2 lizzie lizzie  4096 dic  2 23:24 Descargas
-rwxrwxr-x 1 lizzie lizzie  1052 dic 15 15:22 dispositivos.sh
drwxr-xr-x 4 lizzie lizzie  4096 dic 15 02:07 Documentos
drwxr-xr-x 2 lizzie lizzie  4096 dic 15 17:04 Escritorio
drwxr-xr-x 3 lizzie lizzie  4096 nov 30 19:50 Imágenes
-rw-rw-r-- 1 lizzie lizzie     0 dic 18 18:53 listado.txt
drwxr-xr-x 2 lizzie lizzie  4096 nov  1 18:26 Música
drwxr-xr-x 2 lizzie lizzie  4096 nov  1 18:26 Público
mie 18 dic 2024 18:54:41 CST
```

---
---
### EJERCICIO 3: COPIAR Y MOVER ARCHIVOS
- Se creó un archivo (salida.txt) con el comando echo y se redirigió su salida al archivo. Luego, se leyó el contenido con cat, se agregó más texto al archivo usando >> (sin sobrescribir), y se verificó el contenido actualizado. Este ejercicio mostró cómo manejar archivos mediante redirección en Linux.
```
lizzie@Lizzie-VirtualBox:~$ echo "Hola Mundo" > salida.txt
lizzie@Lizzie-VirtualBox:~$ ls
archivo.txt  Descargas  dispositivos.sh  Documentos  Escritorio  Imágenes  listado.txt  Música  Público  salida.txt
lizzie@Lizzie-VirtualBox:~$ cat < salida.txt
Hola Mundo
lizzie@Lizzie-VirtualBox:~$ echo "Este es un archivo de prueba" >> salida.txt
lizzie@Lizzie-VirtualBox:~$ cat salida.txt
Hola Mundo
Este es un archivo de prueba
``` 
- Se creó un archivo (archivo1.txt) con texto, se copió al directorio /tmp con cp, se renombró a archivo2.txt con mv, y se movió de regreso al directorio actual. El ejercicio enseñó cómo copiar, mover y renombrar archivos desde la terminal.
```
lizzie@Lizzie-VirtualBox:~$ echo "Este es un archivo de prueba" > archivo1.txt
lizzie@Lizzie-VirtualBox:~$ ls
archivo.txt  archivo1.txt  Descargas  dispositivos.sh  Documentos  Escritorio  Imágenes  listado.txt  Música  Público  salida.txt
lizzie@Lizzie-VirtualBox:~$ cp archivo1.txt /tmp/
lizzie@Lizzie-VirtualBox:~$ ls /tmp/
archivo1.txt  systemd-private-XXXX
lizzie@Lizzie-VirtualBox:~$ mv /tmp/archivo1.txt /tmp/archivo2.txt
lizzie@Lizzie-VirtualBox:~$ ls /tmp/
archivo2.txt  systemd-private-XXXX
lizzie@Lizzie-VirtualBox:~$ mv /tmp/archivo2.txt .
lizzie@Lizzie-VirtualBox:~$ ls
archivo.txt  archivo1.txt  archivo2.txt  Descargas  dispositivos.sh  Documentos  Escritorio  Imágenes  listado.txt  Música  Público  salida.txt
lizzie@Lizzie-VirtualBox:~$ cat archivo2.txt
Este es un archivo de prueba
```
---
---
### EJERCICIO 4: COMPRIMIR Y DESCOMPRIMIR ARCHIVOS

#### **Diferencia entre fragmentación interna y externa**

- Se creó un directorio vacío llamado **backup** en el directorio actual del usuario. Este servirá como contenedor para los archivos que se van a respaldar.

- Se copiaron dos archivos (**hostname** y **os-release**) desde el directorio /etc al directorio recién creado backup. Estos archivos se usarán como ejemplo para realizar la compresión.
```
lizzie@Lizzie-VirtualBox:~$ cp /etc/hostname backup/
lizzie@Lizzie-VirtualBox:~$ cp /etc/os-release backup/
```

- Se comprimió el directorio **backup** en un archivo llamado **backup.tar.gz** usando el comando **tar**.

- El directorio **backup** fue eliminado de manera recursiva con **rm -r**. Esto elimina el directorio y todo su contenido, simulando un escenario en el que solo queda el archivo comprimido como respaldo.
```
lizzie@Lizzie-VirtualBox:~$ rm -r backup
```

- Se descomprimió el archivo **backup.tar.gz** usando el comando **tar**.
```
lizzie@Lizzie-VirtualBox:~$ tar -xzvf backup.tar.gz
backup/
backup/hostname
backup/os-release
```
- El directorio **backup** fue restaurado, y el archivo comprimido **backup.tar.gz** sigue presente. Ambos contienen los mismos datos, verificando que el respaldo fue exitoso.
```
lizzie@Lizzie-VirtualBox:~$ ls -l
total 12
drwxr-xr-x 2 lizzie lizzie 4096 dic 18 19:10 backup
-rw-r--r-- 1 lizzie lizzie  142 dic 18 19:08 backup.tar.gz
```

---
---
### EJERCICIO 5: PERMISOS Y PROPIEDADES DE ARCHIVOS

- El comando touch **privado.txt** creó un archivo vacío llamado **privado.txt** en el directorio actual. Este archivo estará disponible con permisos predeterminados.
```
lizzie@Lizzie-VirtualBox:~$ touch privado.txt
```

- El comando **chmod 600 privado.txt** cambió los permisos del archivo para que solo el propietario pueda leer y escribir en él. Otros usuarios no tendrán acceso al archivo.
```
lizzie@Lizzie-VirtualBox:~$ chmod 600 privado.txt
```
- El comando **sudo chown usuario privado.txt** cambió el propietario del archivo **privado.txt** al usuario especificado (usuario). Esto requiere permisos de administrador.
```
lizzie@Lizzie-VirtualBox:~$ sudo chown usuario privado.txt
```
- El comando **ls -l privado.txt** mostró los detalles del archivo, confirmando que ahora tiene permisos de lectura y escritura únicamente para el propietario (-rw-------) y que el propietario fue cambiado al usuario usuario.
```
lizzie@Lizzie-VirtualBox:~$ ls -l privado.txt
-rw------- 1 usuario lizzie 0 dic 18 19:10 privado.txt
```
- El comando **ls -l** enumeró todos los archivos y directorios en el directorio actual, mostrando detalles como permisos, propietarios y fechas de modificación. Se puede verificar que privado.txt tiene los permisos esperados y su propietario fue cambiado a usuario.
```
izzie@Lizzie-VirtualBox:~$ ls -l
total 88
-rw-rw-r-- 1 lizzie lizzie     0 dic 15 18:14 archivo.txt
drwxr-xr-x 2 lizzie lizzie  4096 dic  2 23:24 Descargas
-rwxrwxr-x 1 lizzie lizzie  1052 dic 15 15:22 dispositivos.sh
drwxr-xr-x 4 lizzie lizzie  4096 dic 15 02:07 Documentos
drwxr-xr-x 2 lizzie lizzie  4096 dic 15 17:04 Escritorio
drwxr-xr-x 3 lizzie lizzie  4096 nov 30 19:50 Imágenes
-rw-rw-r-- 1 lizzie lizzie     0 dic 18 18:53 listado.txt
-rw------- 1 usuario lizzie     0 dic 18 19:10 privado.txt
drwxr-xr-x 2 lizzie lizzie  4096 nov  1 18:26 Música
drwxr-xr-x 2 lizzie lizzie  4096 nov  1 18:26 Público
```
---
---
### EJERCICIO 6: EXPLORACIÓN DE DISPOSITIVOS

- El comando lsblk muestra los discos y sus particiones.
```
lizzie@Lizzie-VirtualBox:~$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0   20G  0 disk 
├─sda1   8:1    0   19G  0 part /
└─sda2   8:2    0    1G  0 part [SWAP]
```
- El comando du -sh /home/lizzie/Documentos muestra el tamaño total del directorio Documentos. El parámetro -s indica que solo se mostrará el total y -h hace que el tamaño sea legible (en unidades como KB, MB o GB). En este caso, el directorio Documentos ocupa 4 KB.
```
lizzie@Lizzie-VirtualBox:~$ du -sh /home/lizzie/Documentos
4.0K    /home/lizzie/Documentos
```
- El comando df -h muestra el uso del espacio en disco de todos los sistemas de archivos montados.
```
lizzie@Lizzie-VirtualBox:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/sda1        19G  1.5G   17G   9% /
tmpfs            1.9G  3.5M  1.9G   1% /dev/shm
/dev/sda2        1.0G  32M    968M   4% [SWAP]
```
---
---
### EJERCICIO 7: CREAR Y FORMATEAR PARTICIONES

-En este paso, ejecutamos el comando fdisk -l para listar todos los discos disponibles en el sistema. En este caso, hemos identificado que el disco /dev/sdb está disponible y tiene suficiente espacio para crear una nueva partición. Se observa que no tiene particiones previas o bien tiene una partición básica (/dev/sdb1), que es donde procederemos a crear una nueva partición.
```
lizzie@Lizzie-VirtualBox:~$ sudo fdisk -l
[sudo] password for lizzie: 
Disk /dev/sdb: 10 GiB, 10737418240 bytes, 20971520 sectors
Disk model: VirtualBox  VDI
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x00000000

Device     Boot Start      End  Sectors Size Id Type
/dev/sdb1        2048 20971519 20969472 10G 83 Linux
```
- En este paso, usamos el comando fdisk para iniciar la herramienta de particionado en el disco /dev/sdb. El comando n se utiliza para crear una nueva partición. Al ejecutarlo, fdisk nos pedirá varios detalles, como el tipo de partición y el tamaño, que dejamos en los valores predeterminados para simplificar el proceso.
```
lizzie@Lizzie-VirtualBox:~$ sudo fdisk /dev/sdb
Welcome to fdisk (util-linux 2.37.2).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Command (m for help): n
```
- Después de crear la nueva partición, ejecutamos el comando w para escribir los cambios en el disco. Este paso asegura que la nueva partición sea creada y almacenada en el disco. Luego de ejecutar este comando, fdisk se cierra.
```
Command (m for help): w
The partition table has been altered.
Syncing disks.
lizzie@Lizzie-VirtualBox:~$
```
- Aquí usamos el comando mkfs.ext4 para formatear la partición /dev/sdb1 con el sistema de archivos ext4. El proceso muestra información sobre el formateo, como la creación de inodos y bloques, y confirma que la partición ha sido formateada correctamente.
```
lizzie@Lizzie-VirtualBox:~$ sudo mkfs.ext4 /dev/sdb1
mke2fs 1.46.5 (30-Dec-2021)
Creating filesystem with 2621440 4k blocks and 655360 inodes
Filesystem UUID: e5a35e1d-4ac5-4d1a-bf0f-bfa28b83c7e3
Superblock backups stored on blocks:
        8193, 24577, 40961, 57345, 73729
Writing inode tables: done
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done
```
- En este paso, primero creamos un directorio de montaje en /mnt/nueva_particion usando el comando mkdir. Luego, usamos el comando mount para montar la partición recién formateada en este directorio. Esto nos permite interactuar con la partición como si fuera parte del sistema de archivos principal.
```
lizzie@Lizzie-VirtualBox:~$ sudo mkdir /mnt/nueva_particion
lizzie@Lizzie-VirtualBox:~$ sudo mount /dev/sdb1 /mnt/nueva_particion
```
- Este comando crea un archivo de texto llamado test.txt en la nueva partición montada. Usamos el comando echo para escribir el texto "Prueba de escritura" en el archivo. Este paso verifica que la partición esté funcionando correctamente, permitiendo escribir archivos en ella.
```
lizzie@Lizzie-VirtualBox:~$ echo "Prueba de escritura" > /mnt/nueva_particion/test.txt
```
- Finalmente, para liberar la partición y desmontarla de manera segura, usamos el comando umount. Esto garantiza que los cambios en los archivos sean guardados y que la partición se libere de forma segura para futuras manipulaciones.
```
lizzie@Lizzie-VirtualBox:~$ sudo umount /mnt/nueva_particion
```
---
---
---