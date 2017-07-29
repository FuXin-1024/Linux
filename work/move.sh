#########################################################################
# File Name: move.sh
# Author: fx
# mail: 1007160080qq.com
# Created Time: Sat 29 Jul 2017 07:18:56 AM PDT
#########################################################################
#!/bin/bash

#信号
sigA=20
sigS=21
sigD=22
sigW=23
sig=0

#方块在屏幕上的坐标点
box0=(0 0 0 1 1 0 1 1)

#边界
left=3
top=3

#当前坐标
currentX=15;
currentY=2;

function Draw_Box()
{
	local i j x y
	if (($1 == 0))   #清除以前的方块
	then
		for (( i=0; i<8; i+=2 ))
		do
			(( x = left + 3*(currentX + ${box0[i]} )))
			(( y = top + currentY + ${box0[i+1]} ))
			
		echo -e "\033[${y};${x}H     "
    	done
	else
		echo -e "\033[31m\033[1m"
		for (( i=0; i<8; i+=2 ))
		do
			(( x = left + 3*(currentX + ${box0[i]} )))
			(( y = top + currentY + ${box0[i+1]} ))
			echo -e "\033[${y};${x}H[*]"
		done
	fi
	echo -e "\033[0m"
}

function move_left()
{
	if ((currentX == 0))
	then
		return 1;
	fi

	#先清除以前的方块
	Draw_Box 0

	#改变 x 坐标
	(( currentX -- ))

	#画出新的方块
	Draw_Box 1

	return 0;
}

function move_right
{
	if ((currentX > 20 ));then
		return 1;
	fi

	#先清除以前的方块
	Draw_Box 0

	#改变左标
	(( currentX++ ))

	#画出新的方块
	Draw_Box 1

	return 0;
}

function move_up()
{
	if (( currentY == 0));then
		return 1;
	fi

	#先清除以前的方块
	Draw_Box 0

	#改变 y 坐标
	(( currentY -- ))

	#画出新的方块
	Draw_Box 1

	return 0;
}

function move_down()
{
	if (( currentY > 20 ));then
		return 1;
	fi

	#先清除以前的方块
	Draw_Box 0

	#改变y坐标
	(( currentY++ ))

	#画出新的方块
	Draw_Box 1

	return 1;
}

function Register_Signal()
{
	trap "sig=$sigA;" $sigA
	trap "sig=$sigS;" $sigS
	trap "sig=$sigD;" $sigD
	trap "sig=$sigW;" $sigW
}

function Recive_Signal()
{
	Register_Signal
	Draw_Box 1
	
	while true
	do
		sigThis=$sig

		case "$sigThis" in
			"$sigA")
			move_left
			sig=0
			;;
			
			"$sigS")
			move_down
			sig=0
			;;

			"$sigD")
			move_right
			sig=0
			;;

			"$sigW")
			move_up
			sig=0
			;;

		esac
	done
}

function Kill_Signal()
{
	local sigThis
	while :
	do
		read -s -n 1 key

		case "$key" in
			"W"|"w")
			kill -$sigW $1
			;;

			"S"|"s")
			kill -$sigS $1
			;;

			"A"|"a")
			kill -$sigA $1
			;;

			"D"|"d")
			kill -$sigD $1
			;;

			"Q"|"q")
			kill -9 $1
			exit
		esac
	done
}

if [[ "$1" == "--show" ]];then
	Recive_Signal
else
	bash $0 --show &
	Kill_Signal $!
fi
