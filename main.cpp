#include"common.h"
#include"charactor.h"
#include"huff_tree.h"
#include"encoding.h"
#include"zip.h"
#include"decoding.h"
#include"unzip.h"
using namespace std;

void print_main_menu()
{
	cout << "       made by zq2003       \n";
	cout << "~          wellcome        ~\n";
	cout << "  1.compress  2.decompress  \n";
	cout << "            0.exit          \n";
	cout << "\nyour input:";
}

int main()
{
	while (true)
	{
		print_main_menu();
		int choice = 0;
		cin >> choice;
		switch (choice)
		{
	    	case 1:
	    	{
	    		while (true)
	    		{
	    			cout << "file to be compressed:";
	    			string src_file_name;
	    			cin >> src_file_name;
	    			while (is_file_exist(src_file_name) == false)
	    			{
	    				cout << "file does not exist,please input again(or input 0 to return to the menu):";
	    				cin >> src_file_name;
	    				if (src_file_name == "0")
	    					break;
	    			}
	    			if (src_file_name == "0")
	    				break;
	    			cout << "name the compressed file as:";
	    			string dest_file_name;
	    			cin >> dest_file_name;
	    			while (is_file_exist(dest_file_name) == true)
	    			{
	    				cout << "file already exists\n";
                        cout << " 1.cover 2.re-input";
                        int choose;
                        cin >> choose;
                        if(choose == 1)
                            break;
                        else
	    				    cin >> dest_file_name;
	    			}
	    			cout << "compressing,please wait...\n";
	    			Zip user(src_file_name);
	    			user.ZipFile(dest_file_name);
	    			cout << "success!\n 0.return to menu 1.continue to compress\n";
	    			int choose = 0;
	    			cin >> choose;
	    			while(choose != 0 && choose != 1)
	    			{
	    				cout << "wrong input,try again:";
	    				cin >> choose;
	    			}
	    			if (choose == 0)
	    				break;
	    			else if (choose == 1)
	    				continue;
	    		}
	    	}
	    	break;
	    	case 2:
	    	{
                while(true)
                {
	    	    	cout << "file to be decompressed:";
	    	    	string src_file_name;
	    	    	cin >> src_file_name;
	    	    	while (is_file_exist(src_file_name) == false)
	    	    	{
	    	    		cout << "file does not exist,please input again(or input 0 to return to the menu):";
	    	    		cin >> src_file_name;
	    	    		if (src_file_name == "0")
	    	    			break;
	    	    	}
	    	    	if (src_file_name == "0")
	    	    		break;
	    	    	cout << "name the decompressed file as:";
	    	    	string dest_file_name;
	    	    	cin >> dest_file_name;
	    	    	while (is_file_exist(dest_file_name) == true)
	    	    	{
	    	    		cout << "file already exists\n";
                        cout << " 1.cover 2.re-input";
                        int choose;
                        cin >> choose;
                        if(choose == 1)
                            break;
                        else
	    	    		    cin >> dest_file_name;
                    }
	    	    	cout << "decompressing,please wait...\n";
	    	    	UnZip user(src_file_name);
	    	    	user.UnZipFile(dest_file_name);
	    	    	cout << "success!\n 0.return to the menu 1.continue to decompress\n";
	    	    	int choose = 0;
	    	    	cin >> choose;
	    	    	while (choose != 0 && choose != 1)
	    	    	{
	    	    		cout << "wrong input,try again:";
	    	    		cin >> choose;
	    	    	}
	    	    	if (choose == 0)
	    	    		break;
	    	    	else if (choose == 1)
	    	    		continue;
                }
	    	}
	    	break;
	    	case 0:
            {
	    		cout << "thanks for using\n";
	    		return 0;
            }
            break;
	    	default:
	    	{
	    		cout << "wrong input,try again:";
	    	}
            break;
        }
	}
	return 0;
}
