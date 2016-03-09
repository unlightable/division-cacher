Tom Clancy's Division forces FILE_FLAG_NO_BUFFERING and I don't like it.
Having 10th of GB of RAM lying around unused while HDD rips its ass apart is **NO GOOD**.

So this hack unflags all files cotnaining "rogue" in its path from being unbuffered.

##Do I need it?
If you have over 8GB RAM and most of it is doing nothing - you could use it.
But you won't notice much difference if your game is already installed onto something fast (SSD, wink-wink).

##Building
This thingy depends on [mhook](https://github.com/martona/mhook). Get it and put it directly into this folder.

I'm also too lazy to make it build though anything good, so you just fire up your x64 MSVC environment (`vcvarsall.bat`) and do `build.bat`.
x64 part is *important*.

##Installation
I'm also too lazy to include dll injector. Find it online or rather use [AppInit_DLLs](https://msdn.microsoft.com/en-us/library/windows/desktop/dd744762(v=vs.85).aspx)

##Prebuilts
I'm also too lazy to release it properly, especially since it's kinda gray-area cheat-wise.