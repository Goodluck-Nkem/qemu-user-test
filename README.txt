To run another architecture, we need to use qemu-user.
So install, in addition if we want debug then we need gdb-multiarch.
Now we need to move/symlink certain locations, so that the binary will feel at home.
Otherwise, it won't run!
These locations should be at exactly where a Linux System would look if the bin was running natively.
We don't need to examine each native machine to know.
We can use the info from a compiled binary of the architecture.

One of the locations is the interpreter, I have two methods to get it.
	Method1: readelf -a <bin> | grep interpreter
	Method2: file <bin> | grep interpreter
I prefer method1.

Move the compiler's lib folder or create a symlink in /lib, so that other rt libs can be found. 
Example: sudo ln -s /usr/<compiler>/lib /lib/<compiler>

Then move its interp .so file or create the symlink so that it can startup and run.
Examples: 
	sudo ln -s /lib/<compiler>/<ld_so> /lib
	sudo ln -s /usr/<compiler>/lib/<ld_so> /lib
	sudo ln -s /usr/<compiler>/lib64/<ld_so> /lib64
As seen above the interpreter may want lib or lib64, pay attention.
The first two examples apply to the same test case, choose one.

The following shows how to run/debug.
Run: qemu-<abi> <bin>
Debug: If we want to debug instead, we should use two windows, it's cleaner.
	Window1:
		qemu-<abi> -g <PORT> <bin>
	Window2:
		gdb-multiarch -tui <bin> 
		target remote localhost:<PORT> 
		b main 
		continue

The last 3 commands can be shorthanded by defining a new command in the ~/.gdbinit file.

PS: 
I tested on both PC and Android(termux) but for termux you must run under proot.
Because as you have seen, directories such as /lib and /lib64 needs to be accessed, termux on its own runs like a regular Android app in its app data area.
proot still does, but it tricks any process it spawns to think it starts from a "/" directory. Similar to what a chroot does in a regular PC.

See https://github.com/termux/proot-distro on how to install proot.
Install a distro.
I installed ubuntu, don't worry about size, its in few MB, since it is not a true complete distro.

