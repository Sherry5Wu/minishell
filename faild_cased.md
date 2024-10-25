Evaluation sheet, I haven't test these cases:
1. exit
2. Return value of a process

There are bugs in these function:
3. signal: ctrl +c in a child process:
		   grep "a"
			^C
			jingwu@c1r5p9:~$
4. env: not sure if the results are correct.
5. export: can't add new a variable or replace the old variable.

Going to test 'unset'
 fix export error????????


———————————— builtins
Test   1: ✅ echo hello world
Test   2: ✅ echo "hello world"
Test   3: ✅ echo 'hello world'
Test   4: ✅ echo hello'world'
Test   5: ✅ echo hello""world
Test   6: ✅ echo ''
Test   7: ✅ echo "$PWD"
Test   8: ✅ echo '$PWD'
Test   9: ✅ echo "aspas ->'"
Test  10: ✅ echo "aspas -> ' "
Test  11: ✅ echo 'aspas ->"'
Test  12: ✅ echo 'aspas -> " '
Test  13: ✅ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"
Test  14: ✅ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<'
Test  15: ✅ echo "exit_code ->$? user ->$USER home -> $HOME"
Test  16: ✅ echo 'exit_code ->$? user ->$USER home -> $HOME'
Test  17: ✅ echo "$"
Test  18: ✅ echo '$'
Test  19: ✅ echo $
Test  20: ✅ echo $?
Test  21: ✅ echo $?HELLO
Test  22: ✅ pwd
Test  23: ✅ pwd oi
Test  24: ✅ export hello
Test  25: ✅ export HELLO=123
Test  26: ❌ export A-
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( not a valid identifier)
Test  27: ✅ export HELLO=123 A
Test  28: ✅ export HELLO="123 A-"
Test  29: ✅ export hello world
Test  30: ✅ export HELLO-=123
Test  31: ✅ export =
Test  32: ✅ export 123
Test  33: ✅ unset
Test  34: ✅ unset HELLO
Test  35: ✅ unset HELLO1 HELLO2
Test  36: ✅ unset HOME
Test  37: ✅ unset PATH
Test  38: ✅ unset SHELL
Test  39: ✅ cd $PWD
Test  40: ✅ cd $PWD hi
Test  41: ✅ cd 123123
Test  42: ✅ exit 123
Test  43: ✅ exit 298
Test  44: ✅ exit +100
Test  45: ✅ exit "+100"
Test  46: ✅ exit +"100"
Test  47: ✅ exit -100
Test  48: ✅ exit "-100"
Test  49: ✅ exit -"100"
Test  50: ✅ exit hello
Test  51: ✅ exit 42 world
Test  52: ✅
———————————— pipes
Test  53: ✅ env | sort | grep -v SHLVL | grep -v ^_
Test  54: ✅ cat ./test_files/infile_big | grep oi
Test  55: ✅ cat minishell.h | grep ");"$
Test  56: ✅ export GHOST=123 | env | grep GHOST
———————————— redirects
Test  57: ✅ grep hi <./test_files/infile
Test  58: ✅ grep hi "<infile" <         ./test_files/infile
Test  59: ✅ echo hi < ./test_files/infile bye bye
Test  60: ✅ grep hi <./test_files/infile_big <./test_files/infile
Test  61: ✅ echo <"./test_files/infile" "bonjour       42"
Test  62: ✅ cat <"./test_files/file name with spaces"
Test  63: ✅ cat <./test_files/infile_big ./test_files/infile
Test  64: ✅ cat <"1""2""3""4""5"
Test  65: ✅⚠️  echo <"./test_files/infile" <missing <"./test_files/infile"
mini error = ( Permission denied)
bash error = ( No such file or directory)
Test  66: ✅⚠️  echo <missing <"./test_files/infile" <missing
mini error = ( No such file or directory Permission denied)
bash error = ( No such file or directory)
Test  67: ✅ cat <"./test_files/infile"
Test  68: ✅ echo <"./test_files/infile_big" | cat <"./test_files/infile"
Test  69: ✅ echo <"./test_files/infile_big" | cat "./test_files/infile"
Test  70: ✅ echo <"./test_files/infile_big" | echo <"./test_files/infile"
Test  71: ✅ echo hi | cat <"./test_files/infile"
Test  72: ✅ echo hi | cat "./test_files/infile"
Test  73: ✅ cat <"./test_files/infile" | echo hi
Test  74: ✅ cat <"./test_files/infile" | grep hello
Test  75: ✅ cat <"./test_files/infile_big" | echo hi
Test  76: ✅ cat <missing
Test  77: ✅ cat <missing | cat
Test  78: ✅ cat <missing | echo oi
Test  79: ✅ cat <missing | cat <"./test_files/infile"
Test  80: ✅ echo <123 <456 hi | echo 42
Test  81: ✅ ls >./outfiles/outfile01
Test  82: ✅ ls >         ./outfiles/outfile01
Test  83: ✅ echo hi >         ./outfiles/outfile01 bye
Test  84: ✅ ls >./outfiles/outfile01 >./outfiles/outfile02
Test  85: ✅ ls >./outfiles/outfile01 >./test_files/invalid_permission
Test  86: ✅ ls >"./outfiles/outfile with spaces"
Test  87: ✅ ls >"./outfiles/outfile""1""2""3""4""5"
Test  88: ❌ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"
Only in ./mini_outfiles: outfile02
mini outfiles:
bash outfiles:
Test  89: ✅⚠️  ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission
mini error = ( Permission denied Permission denied)
bash error = ( Permission denied)
Test  90: ✅ cat <"./test_files/infile" >"./outfiles/outfile01"
Test  91: ✅ echo hi >./outfiles/outfile01 | echo bye
Test  92: ✅ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
Test  93: ✅ echo hi | echo >./outfiles/outfile01 bye
Test  94: ✅ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02
Test  95: ✅ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02
Test  96: ✅ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
Test  97: ✅ echo hi >./test_files/invalid_permission | echo bye
Test  98: ❌ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
Only in ./mini_outfiles: outfile01
mini outfiles:
bash outfiles:
cat: './bash_outfiles/*': No such file or directory
Test  99: ✅ echo hi | echo bye >./test_files/invalid_permission
Test 100: ✅ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission
Test 101: ❌ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01
Only in ./mini_outfiles: outfile01
mini outfiles:
bash outfiles:
cat: './bash_outfiles/*': No such file or directory
Test 102: ✅ cat <"./test_files/infile" >./test_files/invalid_permission
Test 103: ✅ cat >./test_files/invalid_permission <"./test_files/infile"
Test 104: ✅ cat <missing >./outfiles/outfile01
Test 105: ❌ cat >./outfiles/outfile01 <missing
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
Test 106: ✅ cat <missing >./test_files/invalid_permission
Test 107: ✅⚠️  cat >./test_files/invalid_permission <missing
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 108: ✅ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
Test 109: ❌ ls >>./outfiles/outfile01
Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ
mini outfiles:
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
Test 110: ❌ ls >>      ./outfiles/outfile01
Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ
mini outfiles:
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
Test 111: ✅ ls >>./outfiles/outfile01 >./outfiles/outfile01
Test 112: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01
Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ
mini outfiles:
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
Test 113: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
Test 114: ❌ ls >>./outfiles/outfile01 >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Files ./mini_outfiles/outfile02 and ./bash_outfiles/outfile02 differ
mini outfiles:
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
Test 115: ✅ ls >>./test_files/invalid_permission
Test 116: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile01
Only in ./mini_outfiles: outfile01
mini outfiles:
bash outfiles:
cat: './bash_outfiles/*': No such file or directory
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 117: ❌ ls >>./outfiles/outfile01 >>./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
Test 118: ❌ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./mini_outfiles: outfile02
mini outfiles:
bash outfiles:
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 119: ✅ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02
Test 120: ✅⚠️  ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 121: ❌ echo hi >>./outfiles/outfile01 | echo bye
Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ
mini outfiles:
bash outfiles:
hi
Test 122: ❌ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
Only in ./bash_outfiles: outfile01
Files ./mini_outfiles/outfile02 and ./bash_outfiles/outfile02 differ
mini outfiles:
bash outfiles:
hi
Test 123: ✅ echo hi | echo >>./outfiles/outfile01 bye
Test 124: ✅ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02
Test 125: ❌ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02
Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ
Files ./mini_outfiles/outfile02 and ./bash_outfiles/outfile02 differ
mini outfiles:
bash outfiles:
hi
bye
Test 126: ✅ echo hi >>./test_files/invalid_permission | echo bye
Test 127: ❌ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
Only in ./mini_outfiles: outfile01
mini outfiles:
bash outfiles:
cat: './bash_outfiles/*': No such file or directory
Test 128: ✅ echo hi | echo bye >>./test_files/invalid_permission
Test 129: ✅ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
Test 130: ✅ cat <minishell.h>./outfiles/outfile
Test 131: ✅ cat <minishell.h|ls
———————————— extras
Test 132: ✅
Test 133: ✅ $PWD
Test 134: ❌ $EMPTY
mini output = (SHELL=/bin/zsh LSCOLORS=Gxfxcxdxbxegedabagacad SESSION_MANAGER=local/c2r6p6.hive.fi:@/tmp/.ICE-unix/68446,unix/c2r6p6.hive.fi:/tmp/.ICE-unix/68446 QT_ACCESSIBILITY=1 COLORTERM=truecolor XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg SSH_AGENT_LAUNCHER=gnome-keyring LESS=-R XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0 XDG_MENU_PREFIX=gnome- GNOME_DESKTOP_SESSION_ID=this-is-deprecated GTK_IM_MODULE=ibus LANGUAGE=en SSH_AUTH_SOCK=/run/user/5920/keyring/ssh XMODIFIERS=@im=ibus DESKTOP_SESSION=ubuntu FT_HOOK_NAME=login-user GTK_MODULES=gail:atk-bridge FT_HOOK_PATHNAME=login-user.d KRB5CCNAME=FILE:/tmp/krb5cc_5920_zgySXQ PWD=/home/jingwu/projects/merge_mini/minishell_tester LOGNAME=jingwu XDG_SESSION_DESKTOP=ubuntu XDG_SESSION_TYPE=x11 GPG_AGENT_INFO=/run/user/5920/gnupg/S.gpg-agent:0:1 SYSTEMD_EXEC_PID=78848 XAUTHORITY=/home/jingwu/.Xauthority XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/jingwu GDM_LANG=en HOME=/home/jingwu LANG=en_US.UTF-8 LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36: XDG_CURRENT_DESKTOP=ubuntu:GNOME VTE_VERSION=6800 XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0 GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/f81f409b_1079_4e14_aec7_c01aa9e1385a XDG_SESSION_CLASS=user TERM=xterm-256color ZSH=/home/jingwu/.oh-my-zsh LIBVIRT_DEFAULT_URI=qemu:///system USER=jingwu GNOME_TERMINAL_SERVICE=:1.567 DISPLAY=:0 SHLVL=1 PAGER=less QT_IM_MODULE=ibus XDG_RUNTIME_DIR=/run/user/5920 DOCKER_HOST=unix:///run/user/5920/docker.sock XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/jingwu/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop PATH=/home/jingwu/bin:/home/jingwu/.local/bin:/usr/local/bin:/home/jingwu/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin MACADDRESS=38:f9:d3:91:df:be GDMSESSION=ubuntu DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/5920/bus MAIL=jingwu@student.hive.fi OLDPWD=/home/jingwu/projects/merge_mini _=../minishell)
bash output = ()
Test 135: ❌ $EMPTY echo hi
mini output = (SHELL=/bin/zsh LSCOLORS=Gxfxcxdxbxegedabagacad SESSION_MANAGER=local/c2r6p6.hive.fi:@/tmp/.ICE-unix/68446,unix/c2r6p6.hive.fi:/tmp/.ICE-unix/68446 QT_ACCESSIBILITY=1 COLORTERM=truecolor XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg SSH_AGENT_LAUNCHER=gnome-keyring LESS=-R XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0 XDG_MENU_PREFIX=gnome- GNOME_DESKTOP_SESSION_ID=this-is-deprecated GTK_IM_MODULE=ibus LANGUAGE=en SSH_AUTH_SOCK=/run/user/5920/keyring/ssh XMODIFIERS=@im=ibus DESKTOP_SESSION=ubuntu FT_HOOK_NAME=login-user GTK_MODULES=gail:atk-bridge FT_HOOK_PATHNAME=login-user.d KRB5CCNAME=FILE:/tmp/krb5cc_5920_zgySXQ PWD=/home/jingwu/projects/merge_mini/minishell_tester LOGNAME=jingwu XDG_SESSION_DESKTOP=ubuntu XDG_SESSION_TYPE=x11 GPG_AGENT_INFO=/run/user/5920/gnupg/S.gpg-agent:0:1 SYSTEMD_EXEC_PID=78848 XAUTHORITY=/home/jingwu/.Xauthority XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/jingwu GDM_LANG=en HOME=/home/jingwu LANG=en_US.UTF-8 LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36: XDG_CURRENT_DESKTOP=ubuntu:GNOME VTE_VERSION=6800 XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0 GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/f81f409b_1079_4e14_aec7_c01aa9e1385a XDG_SESSION_CLASS=user TERM=xterm-256color ZSH=/home/jingwu/.oh-my-zsh LIBVIRT_DEFAULT_URI=qemu:///system USER=jingwu GNOME_TERMINAL_SERVICE=:1.567 DISPLAY=:0 SHLVL=1 PAGER=less QT_IM_MODULE=ibus XDG_RUNTIME_DIR=/run/user/5920 DOCKER_HOST=unix:///run/user/5920/docker.sock XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/jingwu/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop PATH=/home/jingwu/bin:/home/jingwu/.local/bin:/usr/local/bin:/home/jingwu/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin MACADDRESS=38:f9:d3:91:df:be GDMSESSION=ubuntu DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/5920/bus MAIL=jingwu@student.hive.fi OLDPWD=/home/jingwu/projects/merge_mini _=../minishell)
bash output = (hi)
Test 136: ✅ ./test_files/invalid_permission
Test 137: ✅ ./missing.out
Test 138: ✅ missing.out
Test 139: ✅ "aaa"
Test 140: ✅ test_files
Test 141: ✅ ./test_files
Test 142: ✅ /test_files
Test 143: ✅ minishell.h
Test 144: ✅ $
Test 145: ✅ $?
Test 146: ✅ README.md
128/146
