#include "purefunction.h"

#include<QString>
#include<cmath>
struct musicinfo;
enum MoodType;
struct MusicPreference;
musicinfo storehouse[1500]={
    musicinfo(103,"富士山下",2006),
    musicinfo(99,"my heart will go on",1997),
    musicinfo(128,"beautiful now",2015),
    musicinfo(65,"moonlight sonata",1801),
    musicinfo(134,"一千个伤心的理由",1995),
    musicinfo(167,"love the way you lie",2010),
    musicinfo(93,"city of stars",2016),
    musicinfo(75,"free loop",2005),
    musicinfo(112,"summertime sadness",2012),
    musicinfo(115,"胆小鬼",1998),
    musicinfo(79,"K歌之王",2000),
    musicinfo(136,"恶作剧",2008),
    musicinfo(107,"一个像夏天一个像秋天",2006),
    musicinfo(174,"手心的蔷薇",2015),
    musicinfo(110,"payphone",2022),
    musicinfo(86,"肆无忌惮",2018),
    musicinfo(156,"倔强",2004),
    musicinfo(89,"monster",2013),
    musicinfo(69,"突然好想你",2008),
    musicinfo(68,"泡沫",2012),
    musicinfo(81,"for him",2015),
    musicinfo(106,"blueming",2019),
    musicinfo(98,"愚人的国度",2011),
    musicinfo(120,"shots",2015),
    musicinfo(117,"淘汰",2007),
    musicinfo(86,"yellow",2003),
    musicinfo(117,"开始懂了",2007),
    musicinfo(116,"如果你也听说",2007),
    musicinfo(130,"Una Mattina",2004),
    musicinfo(88,"因为爱情",2011),
    musicinfo(128,"带你去找夜生活",2019),
    musicinfo(87,"centuries",2014),
    musicinfo(124,"凄美地",2016),
    musicinfo(93,"duvet",2001),
    musicinfo(128,"匆匆那年",2014),
    musicinfo(139,"a thousand years",2011),
    musicinfo(67,"那些你很冒险的梦",2011),
    musicinfo(65,"那些你很冒险的梦",2018),
    musicinfo(75,"起风了",2018),
    musicinfo(67,"someone like you",2011),
    musicinfo(105,"planet",2006),
    musicinfo(94,"wrecked",2021),
    musicinfo(65,"喜剧之王",2014),
    musicinfo(67,"six feet under",2016),
    musicinfo(172,"re:make",2011),
    musicinfo(139,"somewhere in time",2019),
    musicinfo(80,"有一种悲伤",2018)
};

MusicPreference conversion(MoodType mood,float speed){
    MusicPreference pref;
    float baseBPM=80+6*speed;//基于运动科学研究：跑步配速(km/h)与理想步频(BPM)存在线性关系
        //参考值：慢走(4km/h)→104BPM，慢跑(8km/h)→128BPM，快跑(12km/h)→152BPM
    switch (mood) {
    case Relaxed:
        pref.minBPM = static_cast<int>(baseBPM * 0.6f);
        pref.maxBPM = static_cast<int>(baseBPM * 0.8f);
        pref.startDecade = 1960;
        pref.endDecade = 2020; // 广泛选择舒缓音乐
        pref.moodDescription = "放松舒缓";
        break;

    case Focused:
        pref.minBPM = static_cast<int>(baseBPM * 0.85f);
        pref.maxBPM = static_cast<int>(baseBPM * 1.0f);
        pref.startDecade = 1990;
        pref.endDecade = 2020; // 现代专注音乐
        pref.moodDescription = "专注高效";
        break;

    case Energetic:
        pref.minBPM = static_cast<int>(baseBPM * 1.0f);
        pref.maxBPM = static_cast<int>(baseBPM * 1.2f);
        pref.startDecade = 2000;
        pref.endDecade = 2020; // 现代电子/流行
        pref.moodDescription = "活力四射";
        break;

    case Aggressive:
        pref.minBPM = static_cast<int>(baseBPM * 1.2f);
        pref.maxBPM = static_cast<int>(baseBPM * 1.4f);
        pref.startDecade = 2010;
        pref.endDecade = 2020; // 最新高强度音乐
        pref.moodDescription = "高强度训练";
        break;

    case Melancholy:
        pref.minBPM = static_cast<int>(baseBPM * 0.7f);
        pref.maxBPM = static_cast<int>(baseBPM * 0.9f);
        pref.startDecade = 1970;
        pref.endDecade = 2010; // 经典情感音乐
        pref.moodDescription = "忧郁沉思";
        break;
    }

    return pref;
}
float mdistance(float a1,float b1,float a2,float b2){
    float da=(a1-a2)>0?a1-a2:a2-a1;
    float db=(b1-b2)>0?b1-b2:b2-b1;
    return da+db;
}
musicinfo findyoursong(float bpm,float year){
    float dis=9999999999;
    musicinfo x;
    for(musicinfo song:storehouse){
        if( mdistance(song.bpm,song.release,bpm,year)<dis){
            dis=mdistance(song.bpm,song.release,bpm,year);
            x=song;
        }
    }
    return x;
}
MoodType choosemood(float mood){
    if(mood<-60){
        return Melancholy;
    }
    else if(mood<-20){
        return Relaxed;
    }
    else if(mood<20){
        return Focused;
    }
    else if(mood<60){
        return Energetic;
    }
    else{
        return Aggressive;
    }
}


