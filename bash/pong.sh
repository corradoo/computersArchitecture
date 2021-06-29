board=◄▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬► 

w=$(tput cols)
h=$(tput lines)

len=${#board}
whitespace=`printf "%0.s " $(seq $w)`
pos1=0;
pos2=0;

ballX=$((w/2))
ballY=$((h/2))
velX=1
velY=1

draw_board() { #$1-która paletka przesuniecie $2-Linia $3-Wartość
    echo -en "\033[$2;0H$whitespace"; 
    (( pos1 += $3 ))
    (( pos1 = pos1 < 1 ? w - len : pos1 > w - len ? 1 : pos1 ))
    echo -en "\033[$2;${pos1}H$board"; 

}
draw_board2() { #$1-która paletka przesuniecie $2-Linia $3-Wartość
    echo -en "\033[$2;0H$whitespace"; 
    (( pos2 += $3 ))
    (( pos2 = pos2 < 1 ? w - len : pos2 > w - len ? 1 : pos2 ))
    echo -en "\033[$2;${pos2}H$board";
}


tput civis
tput clear
draw_board 1 0 1
draw_board2 1 $h 1
pl1sc=0
pl2sc=0

while [[ $q != q ]]; 
do
    prevX=$((ballX-velX))
    prevY=$((ballY-velY))
    echo -en "\033[${prevY};${prevX}H "
    echo -en "\033[${ballY};${ballX}H●"
    read -n 1 -s -t 0.07 q
    case "$q" in 
        [aA] ) draw_board 1 0 -1;;
        [dD] ) draw_board 1 0 1;;
        [jJ] ) draw_board2 1 $h -1;;
        [lL] ) draw_board2 1 $h 1;;
    esac
    (( velX = ballX < $w ? velX : -1*velX))
    (( velX = ballX > 1 ? velX : -1*velX))


    #odbicie
    if ((ballY == h)); then
        if (( ballX > pos2 )) && ((ballX < pos2+len)); then 
            (( velY = -1*velY)) ; 
        else 
            let pl2sc++; ballX=$((w/2)); ballY=$((h/2)); velY=1;
        fi 
    fi

    if ((ballY == 1)); then
        if (( ballX > pos1 )) && ((ballX < pos1+len)); then 
            (( velY = -1*velY)) ; 
        else 
            let pl1sc++ ; ballX=$((w/2)); ballY=$((h/2)); velY=-1; 
        fi 
    fi


    ((ballX = ballX+velX))
    ((ballY = ballY+velY))

done
tput cnorm
clear
echo p1: $pl1sc p2: $pl2sc
