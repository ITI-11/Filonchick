menu=1
while [ $menu != 5 ]
do
echo ---
echo Menu:
echo 1. Student
echo 2. Moving files from certain location to certain location
echo 3. 1. Personal catalog. 2. Login time and date
echo 4. Find x
echo 5. Exit
echo ---
echo Choose an option:
read menu
echo ---
case $menu in
1)
	echo Max Khutornoy, uTu-11
	;;
2)
	echo Enter original location:
	read fromloc
	echo Enter the name of the file:
	read name
	echo Enter final location:
	read toloc
	mv $fromloc/$name $toloc
	;;
3)
	cd /home/max/Desktop
	chmod +x jump.sh
	./jump.sh
	echo ---
	cd /home/max
	echo > logon.data
	last  > /home/max/logon.data
	;;
4)
	echo Enter the number of the PC:
	read num
	echo Enter your personal list number:
	read listnum
	echo Enter your age:
	read yage
	x=`expr $num \* $yage`
	xl=`expr $listnum \* $yage`
	xres=`expr $x + $xl`
	echo x is $xres
	;;
5)
	;;
*) 
	Such option does not exist
	;;
esac
echo Press whatever button
read
done
