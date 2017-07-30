#########################################################################
# File Name: box.sh
# Author: fx
# mail: 1007160080qq.com
# Created Time: Sun 30 Jul 2017 04:01:42 AM PDT
#########################################################################
#!/bin/bash

#七种不同的方块的定义
#通过旋转，每种方块的显示的样式可能的种类

box0=(0 0 0 1 1 0 1 1)
box1=(0 2 1 2 2 2 3 2 1 0 1 1 1 2 1 3)
box2=(0 0 0 1 1 1 1 2 0 1 1 0 1 1 2 0)
box3=(0 1 0 2 1 0 1 1 0 0 1 0 1 1 2 1)
box4=(0 1 0 2 1 1 2 1 1 0 1 1 1 2 2 2 0 1 1 1 2 0 2 1 0 0 1 0 1 1 1 2)
box5=(0 1 1 1 2 1 2 2 1 0 1 1 1 2 2 0 0 0 0 1 1 1 2 1 0 2 1 0 1 1 1 2)
box6=(0 1 1 1 1 2 2 1 1 0 1 1 1 2 2 1 0 1 1 0 1 1 2 1 0 1 1 0 1 1 1 2)




#把所有盒子放在box中
box=(${box0[@]} ${box1[@]} ${box2[@]} ${box3[@]} ${box4[@]} ${box5[@]} ${box6[@]})

#每个盒子在box中的偏移量
boxOffset=(0 1 3 5 7 11 15)

#旋转次数
rotateCount=(1 2 2 2 4 4 4)

#颜色数组
colourArry=(31 32 33 34 35 36 37)

#旋转类型
rotateType=-1

#盒子标号
boxNum=-1

#新盒子
newBox=()

#边缘距离
top=3
left=3

#当前x,y坐标
currentX=15
currentY=2

function Draw_Box()
{
  local i j x y
  if (( $1 == 0 ));then
	  for (( i=0;i<8;i+=2))
	  do
	  (( x = left + 3* (currentX + ${newBox[i]}) ))
	  (( y = top + currentY + ${newBox[i+1]} ))

	  echo -e "\033[${y};${x}H   "
  done
  else
	  echo -e "\033[${colourArry[$colorNum]}m\033[1m"
	  for (( i=0;i<8;i+=2 ))
	  do
		  (( x=left +3*(currentX + ${newBox[i]}) ))
		  (( y=top + currentY + ${newBox[i+1]} ))    

		  echo -e "\033[${y};${x}H[*]"
	  done
  fi

	echo -e "\033[0m"
}

function Random_Box()
{
	#随机产生盒子信号
	(( boxNum = $RANDOM % 7 ))
	#随机产生盒子的类型
	(( rotateType = $RANDOM % ${rotateCount[boxNum]} ))
	#随机产生颜色
	(( colourNum = $RANDOM % ${#colourArry[*]} ))

	#找到所在box中的起始位置
	(( j=${boxOffset[boxNum]} *8 + rotateType * 8 ))

	for (( i=0;i<8;i++ ))
	do
		(( newBox[i] = ${box[j+i]} ))
	done
}

while :
do
	Random_Box
	Draw_Box 1
	sleep 1
	Draw_Box 0
done
