#include "colorspace.h"
/*
 *
 *
 *  _channelInfo
 *
 *
 *
*/
void _channelInfo::setInfo(int shift, const char *nameChannel)
{
    this->shift = shift;
    this->nameChannel = QString( nameChannel );
}

void _channelInfo::setInfo(int shift, const QString &nameChannel)
{
    this->shift = shift;
    this->nameChannel = nameChannel ;
}
/*
*
* _colorscpaceChannelStruct
*
*/
_colorscpaceChannelStruct::_colorscpaceChannelStruct (unsigned int channelCount)
{
    channelCount = channelCount;
    channelList  = new _channelInfo[channelCount];
}

void _colorscpaceChannelStruct::setChannelInfo(unsigned int channelNum, unsigned int infoShift, const char* infoName)
{
    setChannelInfo( channelNum,infoShift, QString(infoName));
}

void _colorscpaceChannelStruct::setChannelInfo(unsigned int channelNum, unsigned int infoShift, const QString& infoName)
{
    if ( channelNum > channelCount)
        // Throw exceprtion
        return;
    channelList[channelNum].setInfo( infoShift, infoName );
}

/*
 *
 *
 *  Colorspace
 *
 *
 */

Colorspace::Colorspace()
{
    // Allocate memory 4-all colorspaces
    pColorspaceList = new _colorscpaceChannelStruct*[COLORSPACES_COUNT];
    pColorspaceList[GREY] = new _colorscpaceChannelStruct(1);
    pColorspaceList[GREY]->setChannelInfo(1,0,"Monochrome");

    pColorspaceList[RGB] = new _colorscpaceChannelStruct(3);
    pColorspaceList[RGB]->setChannelInfo(0,0,"Red");
    pColorspaceList[RGB]->setChannelInfo(1,1,"Green");
    pColorspaceList[RGB]->setChannelInfo(2,2,"Blue");

    pColorspaceList[HSL] = new _colorscpaceChannelStruct(3);
    pColorspaceList[HSL]->setChannelInfo(0,0,"Hue");
    pColorspaceList[HSL]->setChannelInfo(1,1,"Saturation");
    pColorspaceList[HSL]->setChannelInfo(2,2,"Lightness");

    pColorspaceList[LAB] = new _colorscpaceChannelStruct(3);
    pColorspaceList[LAB]->setChannelInfo(0,0,"Lightness");
    pColorspaceList[LAB]->setChannelInfo(1,1,"A-component");
    pColorspaceList[LAB]->setChannelInfo(2,2,"B-component");

    pColorspaceList[XYZ] = new _colorscpaceChannelStruct(3);
    pColorspaceList[XYZ]->setChannelInfo(0,0,"X-component");
    pColorspaceList[XYZ]->setChannelInfo(1,1,"Y-component");
    pColorspaceList[XYZ]->setChannelInfo(2,2,"Z-component");

    pColorspaceList[XYZ] = new _colorscpaceChannelStruct(3);
    pColorspaceList[XYZ]->setChannelInfo(0,0,"Y-component");
    pColorspaceList[XYZ]->setChannelInfo(1,1,"U-component");
    pColorspaceList[XYZ]->setChannelInfo(2,2,"V-component");
}

int Colorspace::getChannelCount(int colorspace)
{
    if (colorspace <= COLORSPACES_COUNT)
        return pColorspaceList[colorspace]->channelCount;
    return -1;
}

QString Colorspace::getChannelName(int colorspace, uint channelNumber)
{
    if ( colorspace <= COLORSPACES_COUNT && channelNumber < getChannelCount(colorspace) )
        return pColorspaceList[colorspace]->channelList[channelNumber].nameChannel;
    return QString();
}

int Colorspace::getChannelShift(int colorspace, uint channelNumber)
{
    if ( colorspace <= COLORSPACES_COUNT && channelNumber < getChannelCount(colorspace) )
        return pColorspaceList[colorspace]->channelList[channelNumber].shift;
    return -1;
}

