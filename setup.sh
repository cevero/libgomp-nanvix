export WORKDIR=$HOME/workspace
export TARGET=qemu-riscv32
export PATH=$PATH:$WORKDIR/reinaldo-libgomp-nanvix/utils/toolchain/qemu/bin
export OMP_NUM_THREADS=4
export OMP_THREAD_LIMIT=4
export RISCVGDB=$WORKDIR/reinaldo-libgomp-nanvix/utils/toolchain/riscv32/bin/riscv32-elf-gdb
