#########################################################################
# File Name: sig.sh
# Author: fx
# mail: 1007160080qq.com
# Created Time: Sat 29 Jul 2017 03:23:40 AM PDT
#########################################################################
#!/bin/bash


sigA=20
sigS=21
sigD=22
sigW=23

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

	while true
	do
		sigThis=$sig
		case "$sigThis" in
			"$sigA")
			echo "This is A!"
			sig=0
			;;

			"$sigS")
			echo "This is S!"
			sig=0
			;;

			"$sigD")
			echo "This is D!"
			sig=0
			;;

			"$sigW")
			echo "This is W!"
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


