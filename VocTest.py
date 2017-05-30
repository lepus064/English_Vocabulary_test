import random
import sys

def get_vocs(file_name,dictionary):
    file = open(file_name)
    vocs = []
    count = 0
    for voc in file:
        if(voc.find('#')!=0 and len(voc)> 1):
            temp = voc.split("-")
            temp[0] = temp[0][temp[0].find(' ')+1:-1]
            temp[1] = temp[1][1:-1]
            dictionary[temp[0]] = temp[1]
            vocs.append(temp[0])
    return (vocs,dictionary)

def show_dicts(dictionary):
    for voc in dictionary:
        print(voc,end='\t')
        print(dictionary[voc])

def get_questions(times, vocs, dicts):
    print("\033[2J\033[H",end='')
    for i in range(times):
        random.shuffle(vocs)
        temp_vocs = vocs[0:4]
        right_ans = temp_vocs[0]
        print(temp_vocs[0]+' is :')
        random.shuffle(temp_vocs)
        for j in range(4):
            print(str(j+1)+'.'+dicts[temp_vocs[j]], end='  ')
        while(True):
            try:
                ans = int(input('\nAns: '))-1
                if(ans > 3 or ans < 0):
                    print("Please input a number less than 5!!!")
                    continue
                else:                
                    break
            except ValueError:
                print("Please input a number!!!")

        if(temp_vocs[ans] == right_ans):
            input("Correct!!\nPress Enter to continue...")
            print("\033[2J\033[H",end='')
        else:
            print("Wrong!!!")
            input("The answer is: " +dicts[right_ans]+"\nPress Enter to continue...")
            print("\033[2J\033[H",end='')
    
        


def main():
    if(len(sys.argv) < 2):
        print("Usage: python3 VocTest.py voc.md")
    else:
        dictionary = {}
        vocs = []
        (vocs, dictionary) = get_vocs(sys.argv[1],dictionary)
        op = input("Do you want to review? (Y/n) ")
        if(op != 'n' and op != 'N'):
            print("\033[2J\033[H",end='')
            show_dicts(dictionary)
            input("Press Enter to continue...")
        print("\033[2J\033[H",end='') #clear screen
        num = input("How many questions do you want? (default = 5)")
        try:
            get_questions(int(num), vocs, dictionary)
        except ValueError:
            get_questions(5, vocs, dictionary)


if __name__ == '__main__':
    main()
        