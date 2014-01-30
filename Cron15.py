import os
import datetime
import ftplib

#newname = './RMOB_img/RMOB_'+dt+'.png'
#newnamejpg = './RMOB_upload/'+name+rt+'.jpg'
#newnametxt = './RMOB_upload/'+name+rt+'rmob.TXT'
#rmobnamejpg = 'STOR '+name+rt+'.jpg'
#rmobnametxt = 'STOR '+name+rt+'rmob.TXT'

log = open('log_AutoCron15.txt', 'at')
log.write('Zacatek prenosu ' + 'str(datetime.datetime.now()' )

os.system('./RmobGen -input-./io/Observatory.info')

#os.system('mv ./rmob-export/io/*jpg ./RMOB_upload/rmob.jpg')
#os.rename('./RMOB_upload/rmob.jpg', newnamejpg)

#os.system('mv ./rmob-export/io/*txt ./RMOB_upload/rmob.txt')
#os.rename('./RMOB_upload/rmob.txt', newnametxt)

#os.system('mv ./rmob-export/io/*png ./RMOB_img/rmob.png')
#os.rename('./RMOB_img/rmob.png', newname)

#for fileb in os.listdir("./io/gen/"):
#    if fileb.endswith(".TXT"):
#    	file = open('./io/gen/'+fileb,'rb')		# file to send

session = ftplib.FTP('217.169.242.217','radiodata','meteor')
#session.storbinary('STOR ' + fileb, file)     		# send the file
#file.close()										# close file and FTP

#for filea in os.listdir("./io/gen/"):
#    if filea.endswith(".jpg"):
#    	file = open('./io/gen/' + filea,'rb')    	# file to send

#session.storbinary('STOR ' + filea, file)     		# send the file
#file.close()										# close file and FTP
#print session


for root, dirs, file in os.walk('./io/gen'):
    for fname in file:
        full_fname = os.path.join(root, fname)
        file = open(full_fname, 'rb')
        session.storbinary('STOR /' + fname, file)
        file.close()

session.quit()

os.system('mv ./io/gen/*TXT ./io/old/')
os.system('mv ./io/gen/*jpg ./io/old/')

log.write(' >> ' + 'str(datetime.datetime.now()' + ' - konec prenosu \n')
log.close()
