#include "unicode.h"

using namespace Unicode;

uint Utf8::CP1251Table[256] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
    31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,
    59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,
    87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,
    111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,1026,1027,8218,
    1107,8222,8230,8224,8225,8364,8240,1033,8249,1034,1036,1035,1039,1106,8216,8217,
    8220,8221,8226,8211,8212,8250,8482,1113,8250,1114,1116,1115,1119,160,1038,1118,1032,
    164,1168,166,167,1025,169,1028,171,172,173,174,1031,176,177,1030,1110,1169,181,182,
    183,1105,8470,1108,187,1112,1029,1109,1111,1040,1041,1042,1043,1044,1045,1046,1047,
    1048,1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,1059,1060,1061,1062,1063,
    1064,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076,1077,1078,1079,
    1080,1081,1082,1083,1084,1085,1086,1087,1088,1089,1090,1091,1092,1093,1094,1095,
    1096,1097,1098,1099,1100,1101,1102,1103
};

bool Utf8::isNonCharacter(const uint & unicode) {
    // Unicode has a couple of "non-characters" that one can use internally,
    // but are not allowed to be used for text interchange.
    //
    // Those are the last two entries each Unicode Plane (U+FFFE, U+FFFF,
    // U+1FFFE, U+1FFFF, etc.) as well as the entries between U+FDD0 and
    // U+FDEF (inclusive)

    return (unicode & 0xfffe) == 0xfffe || (unicode - 0xfdd0U) < 16;
}

QByteArray Utf8::bytes(const uint & unicode) {
    QByteArray res;
    bytes(unicode, res);
    return res;
}

void Utf8::bytes(const uint & unicode, QByteArray & res) {
    // 0xxxxxxx
    if (unicode < 0x80)
        res.append((char)unicode);
    // 110xxxxx 10xxxxxx
    else if(unicode < 0x800) {
        res
            .append((char)(MASK2BYTES | unicode >> 6))
            .append((char)(MASKBYTE | (unicode & MASKBITS)));
    }
    // 1110xxxx 10xxxxxx 10xxxxxx
    else if(unicode < 0x10000) {
        res
            .append((char)(MASK3BYTES | unicode >> 12))
            .append((char)(MASKBYTE | (unicode >> 6 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode & MASKBITS)));

    // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    } else if(unicode < 0x200000) {
        res
            .append((char)(MASK4BYTES | unicode >> 18))
            .append((char)(MASKBYTE | (unicode >> 12 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode >> 6 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode & MASKBITS)));
    }
    // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if(unicode < 0x4000000) {
        res
            .append((char)(MASK5BYTES | unicode >> 24))
            .append((char)(MASKBYTE | (unicode >> 18 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode >> 12 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode >> 6 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode & MASKBITS)));
    }
    // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    else if(unicode < 0x8000000) {
        res
            .append((char)(MASK6BYTES | unicode >> 30))
            .append((char)(MASKBYTE | (unicode >> 24 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode >> 18 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode >> 12 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode >> 6 & MASKBITS)))
            .append((char)(MASKBYTE | (unicode & MASKBITS)));
    }
    else qDebug() << "unicode: sheet happened";
}

QString Utf8::str(const QByteArray & bytes) {
    const unsigned char * data = (const unsigned char *)bytes.constData();
    QString output;

    while(*data) {
        // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        if((*data & MASK6BYTES) == MASK6BYTES) {
            output.append(
                QChar(
                    ((*data & 0x01) << 30) | ((*(data + 1) & MASKBITS) << 24)
                    | ((*(data + 2) & MASKBITS) << 18) | ((*(data + 3) & MASKBITS) << 12)
                    | ((*(data + 4) & MASKBITS) << 6) | (*(data + 5) & MASKBITS)
                )
           );
           data += 6;
        }
        // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if((*data & MASK5BYTES) == MASK5BYTES) {
            output.append(
                QChar(
                    ((*data & 0x03) << 24) | ((*(data + 1) & MASKBITS) << 18)
                    | ((*(data + 2) & MASKBITS) << 12) | ((*(data + 3) & MASKBITS) << 6)
                    | (*(data + 4) & MASKBITS)
                )
            );
            data += 5;
        }
        // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if((*data & MASK4BYTES) == MASK4BYTES) {
            output.append(
                QChar(
                    ((*data & 0x07) << 18) | ((*(data + 1) & MASKBITS) << 12)
                    | ((*(data + 2) & MASKBITS) << 6) | (*(data + 3) & MASKBITS)
                )
            );
            data += 4;
        }
        // 1110xxxx 10xxxxxx 10xxxxxx
        else if((*data & MASK3BYTES) == MASK3BYTES) {
            output.append(
                QChar(
                    ((*data & 0x0F) << 12) | ((*(data + 1) & MASKBITS) << 6)
                    | ((*(data + 2) & MASKBITS))
                )
            );
            data += 3;
        }
        // 110xxxxx 10xxxxxx
        else if((*data & MASK2BYTES) == MASK2BYTES) {
            output.append(
                QChar(((*data & 0x1F) << 6) | (*(data + 1) & MASKBITS))
            );
            data += 2;
        }
        // 0xxxxxxx
        else if(*data < MASKBYTE) {
            output.append(QChar(*data));
            ++data;
        }
    }

    return output;
}

QByteArray Utf8::bytesCP1251(const QByteArray & iso_bytes) {
    const unsigned char * data = (const unsigned char *)iso_bytes.constData();
    QByteArray res;

    while(*data) {
        bytes(CP1251Table[*data], res);
        data++;
    }

    return res;
}

QByteArray Utf8::bytesCP1252(const QByteArray & iso_bytes) {
    const unsigned char * data = (const unsigned char *)iso_bytes.constData();
    QByteArray res;

    while(*data) {
//        bytes((unsigned char)*data, res);

        if (*data < 0x80) {
            res.append(*data);
        } else {
            res
                .append(0xc0 | *data >> 6)
                .append(0x80 | (*data & 0x3f));
        }

        data++;
    }

    return res;
}



//Re: [c++] string cp1251 to utf8

//void cp2utf( char* str, char* res ) {
//	static const long utf[ 256 ] = {
//		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
//		31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,
//		59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,
//		87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,
//		111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,1026,1027,8218,
//		1107,8222,8230,8224,8225,8364,8240,1033,8249,1034,1036,1035,1039,1106,8216,8217,
//		8220,8221,8226,8211,8212,8250,8482,1113,8250,1114,1116,1115,1119,160,1038,1118,1032,
//		164,1168,166,167,1025,169,1028,171,172,173,174,1031,176,177,1030,1110,1169,181,182,
//		183,1105,8470,1108,187,1112,1029,1109,1111,1040,1041,1042,1043,1044,1045,1046,1047,
//		1048,1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,1059,1060,1061,1062,1063,
//		1064,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076,1077,1078,1079,
//		1080,1081,1082,1083,1084,1085,1086,1087,1088,1089,1090,1091,1092,1093,1094,1095,
//		1096,1097,1098,1099,1100,1101,1102,1103
//	};

//	int cnt = strlen( str ),
//	i = 0, j = 0;

//	for(; i < cnt; ++i ) {
//		long c = utf[ (unsigned char) str[ i ] ];
//		if( c < 0x80 ) {
//			res[ j++ ] = c;
//		}
//		else if( c < 0x800 ) {
//			res[ j++ ] = c >> 6 | 0xc0;
//			res[ j++ ] = c & 0x3f | 0x80;
//		}
//		else if( c < 0x10000 ) {
//			res[ j++ ] = c >> 12 | 0xe0;
//			res[ j++ ] = c >> 6 & 0x3f | 0x80;
//			res[ j++ ] = c & 0x3f | 0x80;
//		}
//		else if( c < 0x200000 ) {
//			res[ j++ ] = c >> 18 | 0xf0;
//			res[ j++ ] = c >> 12 & 0x3f | 0x80;
//			res[ j++ ] = c >> 6 & 0x3f | 0x80;
//			res[ j++ ] = c & 0x3f | 0x80;
//		}
//	}
//	res[ j ] = '\0';
//}
