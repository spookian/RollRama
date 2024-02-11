
namespace collada
{
	const char* skipToEOL(const char *string)
	{
		char p = 'a';
		int idx = 0;
		while (p != '\n')
		{
			p = string[idx];
			if (p == '\0') break;
			idx++;
		}
		return &(string[idx]);
	}

	const char* skipToSpace(const char *string)
	{
		char p = 'a';
		int idx = 0;
		while (p != ' ')
		{
			p = string[idx];
			if (p == '\0') break;
			idx++;
		}
		return &(string[idx]);
	}

	// only use on strings you know for certain are floats
	float strtof(const char *str)
	{
		float result = 0.0f;
		int idx = 0;
		float deccount = 0.0f;
		bool decimal = false;
		char t = str[idx];

		while (t != ' ' && t != '\n' && t != '\0')
		{
			if (t != '.')
			{
				result += (float)(t - '0');
				result *= 10;
			}
			else
			{
				decimal = true;
			}
			
			idx++;
			if (decimal) deccount += 1.0f;
			t = str[idx];
		}
		
		result *= powf(0.1, deccount);
		return result;
	}
}
