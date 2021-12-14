dd if=/dev/zero of=diskc.img bs=512 count=1000
nasm bootload.asm
dd if=bootload of=diskc.img bs=512 conv=notrunc
bcc -o kernel_c.o -c -ansi kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel_c.o kernel_asm.o

bcc -o shell_c.o -c -ansi shell.c
as86 userlib.asm -o userlib_asm.o
ld86 -o shell -d shell_c.o userlib_asm.o

gcc -o loadFile loadFile.c
#dd if=kernel of=diskc.img bs=512 conv=notrunc seek=3
#dd if=message.txt of=diskc.img bs=512 count=1 seek=30 conv=notrunc

bcc -ansi -c -o tstpr1.o tstpr1.c
as86 -o userlib.o userlib.asm
ld86 -d -o tstpr1 tstpr1.o userlib.o
bcc -ansi -c -o tstpr2.o tstpr2.c
as86 -o userlib.o userlib.asm
ld86 -d -o tstpr2 tstpr2.o userlib.o

./loadFile kernel
./loadFile shell
./loadFile message.txt
./loadFile tstpr1
./loadFile tstpr2
