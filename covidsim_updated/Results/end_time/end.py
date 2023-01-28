
import os

# for i in range(10,40, 2):
#     for j in range(10,40, 2):
#         print(i,j)
#         os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/controllers') 
#         open_file = open('nz_c2_tr.yaml','r')
#         lines = open_file.readlines()
#         string1 =  "    default: "+ str(i) +" \n"
#         lines[18] = string1

#         string2 =  "    default: "+ str(j) +" \n"
#         lines[21] = string2

#         open_file.close()

#         open_file = open('nz_c2_tr.yaml','w')

#         lines = open_file.writelines(lines)

#         open_file.close()

#         os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/Results/end_time')
#         os.system("chmod 777 run.sh")
#         os.system("bash run.sh")

#         os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/Results/end_time/level3_days')
#         cmd = "mv out.csv " + str(i) + "_" + str(j) + ".csv"
#         os.system(cmd)



for i in range(2,10):

    os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/controllers') 
    open_file = open('nz_c2_tr.yaml','r')
    lines = open_file.readlines()
    string1 =  "    default: "+ str(i) +" \n"
    lines[12] = string1

    open_file.close()

    open_file = open('nz_c2_tr.yaml','w')

    lines = open_file.writelines(lines)

    open_file.close()

    os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/Results/end_time')
    os.system("chmod 777 run.sh")
    os.system("bash run.sh")

    os.chdir('/home/sai/Desktop/COVID-19/covidsim_updated/Results/end_time/level0_start')
    cmd = "mv out.csv " + str(i) + ".csv"
    os.system(cmd)

