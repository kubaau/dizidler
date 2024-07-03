#!/bin/sh
export S2_PATH=$1
export DOSBOX_EXE=$2

export S2_DATA=$S2_PATH/DATA

export MAPS=DATA/MAPS
export SOUNDDAT=DATA/SOUNDDAT
export SNG=$SOUNDDAT/SNG
export PICS=GFX/PICS

mkdir -p $MAPS
cp $S2_PATH/$MAPS/MISS200.WLD $MAPS

if [ ! -f $SNG/SNG_0014.MID ]
then
    mkdir -p $SNG
    cp -r $S2_PATH/$SNG $SOUNDDAT
    "$DOSBOX_EXE" XMI2MID.BAT -conf dosbox_cycles_max.conf -exit
    rm $SNG/*.DAT
fi

mkdir -p $PICS
cp $S2_PATH/$PICS/SETUP998.LBM $PICS
