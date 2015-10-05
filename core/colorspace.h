#ifndef COLORSPACE_H
#define COLORSPACE_H
#define COLORSPACES_COUNT 6

#include <QString>

struct _channelInfo
{
    QString      nameChannel;
    unsigned int shift;
public:
    void setInfo( int shift, const QString& nameChannel);
    void setInfo( int shift, const char*    nameChannel);
};

//
struct _colorscpaceChannelStruct
{
        void setChannelInfo ( unsigned int channelNum, unsigned int infoShift, const QString& infoName );
        void setChannelInfo ( unsigned int channelNum, unsigned int infoShift, const char*    infoName );
public :
        // Constructor
        _colorscpaceChannelStruct (unsigned int channelCount);

        unsigned int  channelCount;
        _channelInfo* channelList;

};

// Colorspace helper
// Singletone
class Colorspace
{
    private:
        enum ColorModel  { GREY, RGB, HSL, LAB, XYZ, YUV };
        Colorspace();
        Colorspace( const Colorspace& );
        Colorspace& operator=( Colorspace& );
        _colorscpaceChannelStruct* *pColorspaceList;
        // Init Function
        void initColor ();
    public:
        static Colorspace& getInstance()
        {
            static Colorspace  instance;
            return instance;
        }
        int      getChannelCount (int colorspace);
        QString  getChannelName  (int colorspace, uint num);
        int      getChannelShift (int colorspace, uint num);
};
#endif // COLORSPACE_H
