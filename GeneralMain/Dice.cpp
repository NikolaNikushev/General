#include "stdafx.h"
#include <windows.h>
#include "Dice.h"

	Dice::Dice()
	{
		unKeep();
	}

	//generates random value for a dice.
	int Dice::rollDice()
	{
		int value = currentValue;
		if(!isKept)
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			int start = st.wMilliseconds;
			Sleep(start%100);
			Sleep(5);
			GetLocalTime(&st);
			int end = st.wMilliseconds;
			if(start-end < 0){
				value = (((start - end)*(-1)) % 6);
			}
			else{
				value = ((start - end) % 6);
			}
			 value += 1;
			 if(value > 6){ value = 6;}
			currentValue = value;
		}
		isKept = false;
		return value;
	}

	int Dice::getCurrentValue()
	{
		return currentValue;
	}
	
	bool Dice::getIsKept()
	{
		return isKept;
	}

	void Dice::keep()
	{
		isKept = true;
	}

	void Dice::unKeep()
	{
		isKept = false;
	}
