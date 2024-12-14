import serial
from email.message import EmailMessage
import ssl
import smtplib
ser = serial.Serial('COM10',baudrate=9600)
email_sender = 'milad.azizkhani1999@gmail.com'
email_pass = 'iwgg dfya vjhv vamh'
email_rec = 'milad.azizkhani7878@gmail.com'
while True:
    value = ser.readline()
    valstr = str(value)
    #print(valstr)
    check_list = valstr.split("'")
    #print(check_list)
    for j in check_list:
        if j =='Alarm!!!\\r\\n' :
            print("alarm")
            subject = "Alarm !!!"
            body=""" 
            Your flower is drying, please water it.
            """
            em = EmailMessage()
            em['From'] = email_sender
            em['To'] = email_rec
            em['Subject'] = subject
            em.set_content(body)
            context = ssl.create_default_context()
            with smtplib.SMTP_SSL('smtp.gmail.com', 465, context=context) as smtp:
                smtp.login(email_sender, email_pass)
                smtp.sendmail(email_sender, email_rec, em.as_string())
        elif j =='Thanks for watering !\\r\\n' :
            print ("Condition is OK!")
            subject = "Thanks Message"
            body=""" 
            Condition is ok, tnx for watering, Good luck.
            """
            em = EmailMessage()
            em['From'] = email_sender
            em['To'] = email_rec
            em['Subject'] = subject
            em.set_content(body)
            context = ssl.create_default_context()
            with smtplib.SMTP_SSL('smtp.gmail.com', 465, context=context) as smtp:
                smtp.login(email_sender, email_pass)
                smtp.sendmail(email_sender, email_rec, em.as_string())
        
    

