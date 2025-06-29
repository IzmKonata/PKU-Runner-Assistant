#ifndef PUREFUNCTION_H
#define PUREFUNCTION_H

#include<QString>
#include<cmath>
struct musicinfo
{
    musicinfo(){}
    musicinfo(int bpm,const QString&name,int release):bpm(bpm),name(name),release(release){}
    int bpm;
    QString name;
    int release;
};
enum MoodType {
    Relaxed,       // 放松：冥想、瑜伽等
    Focused,       // 专注：工作、学习
    Energetic,     // 精力充沛：有氧运动
    Aggressive,    // 高强度：冲刺训练
    Melancholy     // 忧郁：恢复性运动
};
struct MusicPreference {
    float minBPM;
    float maxBPM;
    float startDecade; // 音乐年代起始（如1990表示1990s）
    float endDecade;   // 音乐年代结束
    QString moodDescription;
};

extern MusicPreference conversion(MoodType mood,float speed);
extern float mdistance(float a1,float b1,float a2,float b2);
extern musicinfo findyoursong(float bpm,float year);
extern MoodType choosemood(float mood);

#endif // PUREFUNCTION_H
