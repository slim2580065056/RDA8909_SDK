@echo off

rem This script will be used by buildbot to build on Windows.
rem It should be executed from top directory "soft".

rem For local test
if not defined bb_revision set bb_revision=unknown
if not defined bb_product set bb_product=dev_unknown
if not defined BB_GIT_EXE set BB_GIT_EXE=C:\Program Files\Git\bin\git.exe
if not defined BB_PYTHON_EXE set BB_PYTHON_EXE=C:\Python27\python.exe
if not defined BB_GIT_BASH_DIR set BB_GIT_BASH_DIR=C:\Program Files\Git\usr\bin\
if not defined BB_CSDTK42_DIR set BB_CSDTK42_DIR=C:\CSDTK4.2\
if not defined BB_SVN_EXE set BB_SVN_EXE=C:\Program Files\CollabNet\Subversion Client\svn.exe

rem Refer to buildconfig.sh for format of %1
set TARGET_PARAM=%1
set ZIP="%BB_7Z_EXE%"
set SCP="%BB_GIT_BASH_DIR%\scp.exe" -oStrictHostKeyChecking=no
set SSH="%BB_GIT_BASH_DIR%\ssh.exe" -oStrictHostKeyChecking=no
set HOME=%BB_GIT_BASH_HOME%
set PYTHON="%BB_PYTHON_EXE%"
set CYGPATH="%BB_GIT_BASH_DIR%cygpath.exe"
set BUSYBOX="%BB_CSDTK42_DIR%make\busybox.exe"
set RES_HOST=%bb_res_host%
set RES_PATH=%bb_res_path%/win

(echo %TARGET_PARAM%| findstr /R /C:"modem-.*-debug")>NUL && goto build_target
(echo %TARGET_PARAM%| findstr /R /C:"modem-.*-release")>NUL && goto build_target
(echo %TARGET_PARAM%| findstr /R /C:"modemdb-.*-debug")>NUL && goto build_target
(echo %TARGET_PARAM%| findstr /R /C:"modemdb-.*-release")>NUL && goto build_target
(echo %TARGET_PARAM%| findstr /R /C:"phone-.*-debug")>NUL && goto build_target
(echo %TARGET_PARAM%| findstr /R /C:"phone-.*-release")>NUL && goto build_target
echo Unknown target: %TARGET_PARAM%
goto failed

:build_target
(echo %TARGET_PARAM%| %BUSYBOX% cut -d- -f1) > tmp.txt && set /P BUILD_TYPE= < tmp.txt
(echo %TARGET_PARAM%| %BUSYBOX% cut -d- -f2) > tmp.txt && set /P CT_TARGET= < tmp.txt
(echo %TARGET_PARAM%| %BUSYBOX% cut -d- -f3) > tmp.txt && set /P CT_RELEASE= < tmp.txt
(%CYGPATH% -am .) > tmp.txt && set /p SOFT_WORKDIR= < tmp.txt
(%CYGPATH% -aw .) > tmp.txt && set /p SOFT_WINWORKDIR= < tmp.txt

call %BB_CSDTK42_DIR%CSDTKvars.bat || goto failed
set PATH=%SOFT_WINWORKDIR%env\utils;%SOFT_WINWORKDIR%env\win32;%PATH%
set CT_PRODUCT=%bb_product%
set CT_OPT=dbg_size
set WITHOUT_WERROR=y
set HEX=%CT_TARGET%_%CT_PRODUCT%_%CT_RELEASE%
IF EXIST .git (
set WITH_GIT=1
set WITH_SVN=0
) ELSE IF EXIST .svn (
set WITH_GIT=0
set WITH_SVN=1
) ELSE (
set WITH_GIT=0
set WITH_SVN=0
)
%SSH% %RES_HOST% mkdir -p %RES_PATH% || goto failed
call:build_%BUILD_TYPE%

echo "DONE"
exit /B %ERRORLEVEL%

rem function build_phone
:build_phone
make -r -j%NUMBER_OF_PROCESSORS% CT_RESGEN=yes CT_USERGEN=no || goto build_phone_return
cd hex\%HEX% || goto build_phone_return
%ZIP% a -tzip ..\..\%HEX%.zip || goto build_phone_return
cd ..\.. || goto build_phone_return
%SCP% %HEX%.zip %RES_HOST%:%RES_PATH%/ || goto build_phone_return
:build_phone_return
exit /B %ERRORLEVEL%

rem function build_modem
:build_modem
make -r -j%NUMBER_OF_PROCESSORS% CT_RESGEN=no CT_USERGEN=no || goto build_modem_return
cd hex\%HEX% || goto build_modem_return
%ZIP% a -tzip ..\..\%HEX%.zip || goto build_modem_return
cd ..\.. || goto build_modem_return
%SCP% %HEX%.zip %RES_HOST%:%RES_PATH%/ || goto build_modem_return
:build_modem_return
exit /B %ERRORLEVEL%

rem function build_modemdb
:build_modemdb
make -r -j%NUMBER_OF_PROCESSORS% CT_RESGEN=no CT_USERGEN=no || goto build_modemdb_return
make -C toolpool/blfota -r -j%NUMBER_OF_PROCESSORS% CT_RESGEN=no CT_USERGEN=no || goto build_modemdb_return
%PYTHON% env/utils/dual_boot_merge.py --bl="hex/%HEX%/blfota_%HEX%_flash.lod" --lod="hex/%HEX%/%HEX%_flash.lod" --output="hex/%HEX%/merge_%HEX%_flash.lod" || goto build_modemdb_return
cd hex\%HEX% || goto build_modemdb_return
%ZIP% a -tzip ..\..\%HEX%.zip || goto build_modemdb_return
cd ..\.. || goto build_modemdb_return
%SCP% %HEX%.zip %RES_HOST%:%RES_PATH%/ || goto build_modemdb_return
:build_modemdb_return
exit /B %ERRORLEVEL%

rem function trim
:trim
set %2=%1
goto :eof

:failed
echo "Failed"
exit /B %ERRORLEVEL%
