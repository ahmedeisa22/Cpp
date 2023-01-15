#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include "clsDate.h"
#include "clsString.h"
using namespace std;
class clsUtil
{
public:
	static void Srand() {
		srand((unsigned)time(NULL));
	}
    template<typename T>
	static T RandomNumber(T From, T To)
	{
		return rand() % (To - From) + From;
	}
    /*
    static enum enCharType { SamallLetter = 1, CapitalLetter = 2, Digit = 3,MixChar = 4 };
    static char GetRandomCharacter(enCharType CharType)
    {
      if (CharType == enCharType::MixChar) {
            CharType = (enCharType)RandomNumber<short>(1, 4);
        }
        switch (CharType)
        {
        case enCharType::SamallLetter:
            return (char)RandomNumber(97, 122);

        case enCharType::CapitalLetter:
            return (char)RandomNumber(65, 90);

        case enCharType::Digit:
            return (char)RandomNumber(48, 57);


        }
    }

    */
    static enum enCharType { SamallLetter = 1, CapitalLetter = 2, Digit = 3, MixChar = 4 };
    static char GetRandomCharacter(enCharType CharType)
    {
        switch (CharType)
        {
        case enCharType::SamallLetter:
            return (char)RandomNumber(97, 122);

        case enCharType::CapitalLetter:
            return (char)RandomNumber(65, 90);

        case enCharType::MixChar:
            return GetRandomCharacter((enCharType)RandomNumber(1,4));

        case enCharType::Digit:
            return (char)RandomNumber(48, 57);


        }
    }
    static string GenerateWord(enCharType CharType, short length)
    {
        string word = "";

        for (int i = 1; i <= length; i++)
            word += GetRandomCharacter(CharType);

        return word;
    }
    static string GenerateKey(enCharType CharType)
    {
        string key = "";

        key += GenerateWord(CharType, 4) + '-';
        key += GenerateWord(CharType, 4) + '-';
        key += GenerateWord(CharType, 4) + '-';
        key += GenerateWord(CharType, 4);

        return key;
    }
    static void GenerateKeys(enCharType CharType,short len)
    {
        for (int i = 1; i <= len; i++)
        {

            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }
    template<typename T >
    static void Swap(T& a, T& b) {
        T tem = a;
        a = b;
        b = tem;

    }
    template<typename T>
    static void shuffleArray(T arr[100], int len)
    {
        for (int i = 0; i < len; i++)
            Swap(arr[RandomNumber(1, len) - 1], arr[RandomNumber(1, len) - 1]);
    }

    template<typename T>
    static void FillArrayWithRandom(T arr[100],int len,int from , int to)
{
    for(int i = 0 ; i < len ; i++)
    {
        arr[i] = RandomNumber(from,to);

    }
}
    template<typename T>
    static void FillArrayWithRandomWords(T arr[100], int len, enCharType CharType, short Wordlen)
    {
        for (int i = 0; i < len; i++)
        {
            arr[i] = GenerateWord(CharType, Wordlen);

        }
    }
    
    template<typename T>
    static void FillArrayWithRandomKeys(T arr[100], int len, enCharType CharType)
    {
        for (int i = 0; i < len; i++)
        {
            arr[i] = GenerateKey(CharType);

        }
    }

    static string Tabs(int Number)
    {
        string t = "";
        for (int i = 0; i < Number; i++)
        {
            t += "\t";
        }
        return t;
    }

    static string encryptedName(string name,int key = 2)
{
    string encrpt = "";
    for(int i = 0 ; i < name.size() ; i++)
        encrpt += name[i] + key;

    return encrpt;
}

    static string decryptedName(string name, int key = 2)
{
    string encrpt = "";
    for(int i = 0 ; i < name.size() ; i++)
        encrpt += name[i] - key;

    return encrpt;
}

    static string NumberToText(int num) {
        if (num == 0)
            return "";

        if (1 <= num && num <= 19) {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven", "Eight","Nine","Ten",
                "Eleven","Twelve","Thirteen","Fourteen", "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
            return arr[num];
        }
        else if (20 <= num && num <= 99) {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return arr[num / 10] + " " + NumberToText(num % 10);
        }
        else if (100 <= num && num <= 199) {

            return "One hundred " + NumberToText(num % 100);
        }
        else if (200 <= num && num <= 999) {
            return NumberToText(num / 100) + " hundreds " + NumberToText(num % 100);
        }
        else if (1000 <= num && num <= 1999) {
            return  "One thousand " + NumberToText(num % 1000);
        }
        else if (2000 <= num && num < 9999999) {
            return NumberToText(num / 1000) + " thousands " + NumberToText(num % 1000);
        }
        else if (1000000 <= num && num <= 1999999) {
            return "One Milion " + NumberToText(num % 1000000);
        }
        else if (2000000 <= num && num <= 999999999) {
            return NumberToText(num / 1000000) + " Milions " + NumberToText(num % 1000000);
        }
        else if (1000000000 <= num && num <= 1999999999) {
            return "One Bilion " + NumberToText(num % 1000000000);
        }
        else {
            return NumberToText(num / 1000000000) + " Bilions " + NumberToText(num % 1000000000);
        }
    }

};

