#include "../include/string.h"
uint16 strlength(string ch)
{
        uint16 strCount = 0;           //compteur à 0
        while(ch[strCount++]);
        return strCount-1;               //on lui soustrait 1
}


uint8 strEql(string ch1,string ch2) //fonction de recherche d'égalité
{
        uint8 result = 1;
        uint8 size = strlength(ch1);
        if(size != strlength(ch2)) result =0;
        else
        {
        uint8 i = 0;
        for(i;i<=size;i++)
        {
                if(ch1[i] != ch2[i]) result = 0;
        }
        }
        return result;
}

char *strchr(const char *p, int ch) //fonction pour chercher un caractère dans un string
{
	char c;
	c = ch;
	for (;; ++p) {
		if (*p == c) return ((char *)p);
		if (*p == '\0') return (NULL);
	}
}
