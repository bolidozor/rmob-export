import os
import datetime
import ftplib

dt = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

log = open('log_AutoCron15.txt', 'at')
log.write('Zacatek prenosu '+ dt )

os.system('./RmobGen -input-./io/Observatory.info')

#os.system('mv ./rmob-export/io/*jpg ./RMOB_upload/rmob.jpg')
#os.rename('./RMOB_upload/rmob.jpg', newnamejpg)

#os.system('mv ./rmob-export/io/*txt ./RMOB_upload/rmob.txt')
#os.rename('./RMOB_upload/rmob.txt', newnametxt)

#os.system('mv ./rmob-export/io/*png ./RMOB_img/rmob.png')
#os.rename('./RMOB_img/rmob.png', newname)


session = ftplib.FTP('217.169.242.217','radiodata','meteor')

for root, dirs, file in os.walk('./io/gen'):
	for fname in file:
		full_fname = os.path.join(root, fname)
		file = open(full_fname, 'rb')
		session.storbinary('STOR /' + fname, file)
		file.close()

session.quit()

os.system('mv ./io/gen/*TXT ./io/old/')
os.system('mv ./io/gen/*jpg ./io/old/')

log.write(' >> ' + dt + ' - konec prenosu \n')
log.close()
