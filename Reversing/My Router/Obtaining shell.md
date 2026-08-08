

I started by looking at the open ports of my router, i saw that it had ssh and a web server.
i had a username and password that i got from the ISP company, i tried logging with that username and password to the website and succeded:
```
	Username: admin
	password: 0MV873Q3Q6LU
```


![[Pasted image 20250922012753.png]]

from there my next goal was to try and ssh into the router, so i started going through the option to check if there is something to do with the ssh (also in the same time i tried to login to the ssh via the credentials i got from the ISP, it did not work :( ).

when looking through the features in the website i came across the ability to send a ping from the router
![[Pasted image 20250922012926.png]]
I thought to myself, wow this is interesting, maybe i can run code using this, i tried some things and i was able to print an environment variable:
![[Pasted image 20250922013029.png]]
which made me realize that its just the ping command ran by bash, i tried command substation and succeded.
![[Pasted image 20250922014054.png]]
![[Pasted image 20250922013123.png]]   
sadly, not all chars are allowed, some of the important ones (space, <, >, \, ", {}) were not allowed on the client side, and when i tried to send them directly using postman i realized that they were also not allowed on the server side😢
from there i tried to use bash tricks to get some of the signs, i was able to get space using the variable $IFS, which was nice, i also learnt about many ways to trigger the bash variable expansion even when {} are not used, i have found that when looking for the variable name bash will stop with one of the following signs: ',/,-, $
which made me be able to do some cool stuff like this:
![[Pasted image 20250922013600.png]]
from here i explored the system a bit more, i looked through interesting files like /etc/passwd and /etc/shadow.
i have found out that most of the file system is squashfs and by that read only, and the writeable stuff are mostly just tmpfs.
with that they have done some funny stuff like making /etc/passwd a symbolic link to /var/passwd to make it writeable.
![[Pasted image 20250922013842.png]]
![[Pasted image 20250922013959.png]]
after realizing that i tried to run passwd -d root to reset root password and access the ssh, sadly it did not work and i saw not able to see the errors because they were in stderr and i was able to see stdout only.
For a time i tried to look for a way to do redirection without < or > in order to see the errors i got but i was not able to do that😢
fortunately i had strace on the machine, i planned to use that to run the command and see its stderr through the strace output, sadly strace output was printed to stderr but strace has an option to choose an output file😊
![[Pasted image 20250922014412.png]]
i planned to use this option to print all output to /dev/stdout, i tried that and it worked!!! i was able to see stderr of commands now.
when i looked at the error it said that passwd failed because it was unable to create the lock file in /etc, which makes sense because /etc is readonly.
I tried to research about ways to go over this limit, and the best way i found was to mount /etc as tmpfs and move my files there, i planned to use unshare at first but sadly it was not installed on the machine.
i tried many things but in the end i was able to do this script:
which mounts /etc as tmpfs, copies /var/shadow to /etc/shadow, runs passwd -d, copies /etc/shadow to /var/shadow and then umounts /etc
```bash
$(export$IFS$(echo$IFS'TEST=tmpfs');export$IFS$(echo$IFS'TEST2=passwd');mount$IFS-t$IFS$(echo$IFS$TEST)$IFS$(echo$IFS$TEST)$IFS/etc;ln$IFS-s$IFS/var/passwd$IFS/etc/passwd;cp$IFS/var/shadow$IFS/etc/shadow;strace$IFS-o$IFS/dev/stdout$IFS$(echo$IFS$TEST2)$IFS-d$IFS$(whoami);cp$IFS/etc/shadow$IFS/var/shadow;umount$IFS/etc)
```

and then all i had to do was copy /var/shadow2 to /var/shadow
and because of the symbolic link from /etc/shadow to /var/shadow it also updated /etc/shadow and i was able to login to the shell without a password 😊
![[Pasted image 20250922015032.png]]

and from there i moved to [[Exploring the file system]]