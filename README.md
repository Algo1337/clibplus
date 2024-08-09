<div align="center">
 <h1>C Mixed System Standard Lib Extension</h1>
 <p>A complete system built-in mixed standard C library package using the minimial libraries that comes with just about any linux OS</p>
</div>

# About

This is a package that extend the minimum linux built-in packages to abstract low-level functions. View the list of included libraries for more information.
Please note that using this package can increase binary size due to certain libs being used within each-other. Which wouldn't be any difference from using a higher-level language. If you aren't creating application that will proform protection check-sum operation and need better proformance.

<b>Why?</b>

To avoid re-inventing the wheels for future projects and to attract more developer to move to C and have to start with that isn't gonna kill their motivation in the process of learning when approaching memory management

# Coming Soon

- An application serving as a github-based repo package manager. Allowing you to download certain libs from this repo from linux CMD-Line (ex: ctypes -i net -extra)

# Progress

<p>Symbol Definitions:<p>

<p>✅ = Completed<br />🛠️ = Being Worked On<br />⚠️ = Needs Work</p>

```
✅⚠️    String Lib ( Could Use More Higher-Level Methods that abstract Lower-Level string Operations )
✅⚠️    Array Lib ( Could use more Higher-Level Methods similar to higher-level language(s) array module(s) )
🛠️⚠️    Map Lib
⚠️      Request Lib
⚠️      Web Server Lib
```

# Install

Installing the extension library is just as easy as 

```
git clone https://https://github.com/advancedalgorithm/C-System-Mixed-Standard-Lib-Extension-Package.git
cd C-System-*; make build; make cp
```

*Include the header*

```
#include <C_TYPES/c_types.h>
```

*Compile flag*

```
<C_TYPES/c_types.h>         : -lctypes
<C_TYPES/Net/Socket.h>      : -lctypes
<C_TYPES/Net/request.h>     : -lssl -lcrypto
```
