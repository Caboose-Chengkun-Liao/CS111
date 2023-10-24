

#include <iostream>
#include <string>
using namespace std;

char e_ch[10], n_ch[10], m_ch[10];
char input_message[100];
int p, q, phi, d, m, e, n;

void inval_pub()
{
	cout << "Public key is not valid!" << endl;
}

void pkey_in() //get e,n
{
	cin.getline(e_ch, 10, ' ');
	cin.clear();
	cin.getline(n_ch, 10, '\n');
	cin.clear();
	e = stoi(e_ch);
	n = stoi(n_ch);
}

void m_input() //get m
{
	cin.getline(m_ch, 10, '\n');
	cin.clear();
	m = stoi(m_ch);
}

void message_input() //get message
{
	cin.getline(input_message,100);
	cin.clear();
}

int main()
{

	pkey_in();
	m_input(); //get m
	message_input(); //get encrypted message

	for (int i = 2; i <= n; i++) //Find p,q
	{
		if (n % i == 0)
		{
			p = i;
			q = n / i;

			if (q % p == 0 || p == q || q == 1)
			{
				inval_pub();
				return 0;
			}
			else
			{
				for (int j = 2; j < q; j++) //Judge if q is prime
				{
					if (q % j == 0)
					{
						inval_pub();
						return 0;
					}
					else continue;
				}
				break;
			}
		}
		else continue;
	}

	phi = (p - 1) * (q - 1);
	if (phi % e == 0)
	{
		inval_pub();
		return 0;
	}

	

	//---------------------------------save encrypted messages---------------------------------

	int dig = 0;

	int encr_mesg[100];

	for (int i = 0; i < m; i++)
	{
		encr_mesg[i] = (input_message[dig] - '0') * 10 + (input_message[dig + 1] - '0');
		dig += 3;
	}
	//-------------------------------------------------------------------------------------------------

	for (int l = 0; (e * l) % phi != 1;) // count d
	{
		l++;
		d = l;
	}

	cout << p << " " << q << " " << phi << " " << d << endl; // first line

	int pow1;
	int remain;
	int now;

	int decr_mesg[100];
	int origin_encri;

	for (int i = 0; i < m; i++)
	{
		decr_mesg[i] = encr_mesg[i];
		for (int j = 1; j < d; j++)
		{
			decr_mesg[i] = (((int(decr_mesg[i]) % n) * encr_mesg[i]) % n);
		}
	}


	for (int i = 0; i < m; i++) // second line
	{
		cout << decr_mesg[i] << " ";
	}
	cout << endl;

	const int x = 5;
	char text_mesg;

	for (int i = 0; i < m; i++) // third line
	{
		switch (decr_mesg[i])
		{
		case x + 26: cout << " "; break;

		case x + 27: cout << "\""; break;

		case x + 28: cout << ","; break;

		case x + 29: cout << "."; break;

		case x + 30: cout << "\'"; break;

		default:
		{
			text_mesg = decr_mesg[i] - x + 65;
			cout << text_mesg;
			break;
		}
		}
	}

	return 0;
}