#%%
#리스트 안에 리스트 -> 중첩 리스트
fruits = ["딸기", "복숭아","배", "천도복숭아","사과", "포도","체리", "블루베리"]
vegetables = ["시금치", "케일", "피망", "강낭콩"]

dirty_dozen = [fruits, vegetables]

print(dirty_dozen)
# %%
import random
rock = '''
    _______
---'   ____)
      (_____)
      (_____)
       (____)
---.__(___)
'''

paper = '''
    _______
---'   ____)____
          ______)
         _______)
         _______)
---.__________)
'''

scissors = '''
    _______
---'   ____)____
          ______)
      __________)
      (____)
---.__(___)
'''
img_hands = [rock, paper, scissors]

my_choice = int(input("무엇을 내겠습니까? 바위(0), 보(1), 가위(2)"))
if my_choice >=3 or my_choice < 0:
    print("잘못된 숫자를 입력했습니다")
# 아예 다른 숫자를 입력했을 경우
else:
    print(f"나의 선택은: ")
    print(img_hands[my_choice])
    computer_choice = random.randint(0, 2)
    print(f"컴퓨터의 선택은: ")
    print(img_hands[computer_choice])

    # 바위(0) > 가위(2) , 바위(0) = 바위(0) , 바위(0) < 보(1) -- 예외처리 0 > 2
    # 보(1) > 바위(0) , 보(1) = 보(1), 보(1) < 가위(2)
    # 가위(2) > 보(1), 가위(2) = 가위(2), 가위(2) < 바위(0) -- 예외처리 2 < 0
    if computer_choice == 0 and my_choice == 2:
        print("컴퓨터가 이겼다")
    elif my_choice == 0 and computer_choice == 2:
        print("내가 이겼다!")
    elif computer_choice > my_choice:
        print("컴퓨터가 이겼다")
    elif my_choice == computer_choice:
        print("비겼다!")
    elif my_choice > computer_choice:
        print("내가 이겼다!")

# %%
import random

number = random.randint(1, 100)

num_of_guess = 0

while True :
    guess = int(input("1부터 100까지의 숫자를 입력하세요 : "))

    num_of_guess += 1

    if guess > number :
        print("입력한 숫자가 너무 큽니다")

    elif guess < number :
        print("입력한 숫자가 너무 작습니다")

    else :
        print(f"축하합니다! {num_of_guess}회 만에 숫자를 맞췄습니다!")
        break

# %%
import socket
hostname = socket.gethostname()
ip_address = socket.gethostbyname(hostname)

print("내부 IP : " + ip_address)
# %%
import pyttsx3

engine = pyttsx3.init()
engine.setProperty('rate', 150)

def speak(text):
    engine.say(text)
    engine.runAndWait()

text = "안녕하세요 파이썬 연습중입니다"
speak(text)
# %%
from gtts import gTTS
from playsound import playsound
text = input('텍스트를 입력하세요: ')
tts = gTTS(text, lang='ko')
tts.save('output.mp3')
playsound('output.mp3')

# %%
import qrcode
import os 
data = "Hi Hello"

img = qrcode.make(data)

file_path = os.path.join("", "qrcode1.png")
img.save(file_path)
# %%
import qrcode
import os

file_path = os.path.join("", "Hello.txt")

def create_qrcode(data):
    img = qrcode.make(data)

    img_file_path = os.path.join("", f"qrcode_{data}.png")
    img.save(img_file_path)

with open(file_path, 'r') as f:
    for line in f:
        data = line.strip()
        create_qrcode(data)
# %%
import psutil
import time

while True:
    cpu_percent = psutil.cpu_percent(interval=None)
    print(f"CPU 사용량 : {cpu_percent}%")

    mem = psutil.virtual_memory()
    mem_percent = mem.percent
    print(f"메모리 사용량 : {mem_percent}%")

    net_io_counters = psutil.net_io_counters()
    bytes_sent = net_io_counters.bytes_sent
    bytes_recv = net_io_counters.bytes_recv
    print(f"네트워크 사용량 : 송신 = {bytes_sent}, 수신 = {bytes_recv}")

    time. sleep(1)

# %%
import itertools
import zipfile
def crack_zip_password(zipfilename, digits=True, letters=True, max_length=9):
    chars = ""
    if digits:
        chars += "0123456789"
    if letters:
        chars += "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    passwords = itertools.chain.from_iterable(
        itertools.product(chars, repeat=i) for i in range(1, max_length + 1)
    )
    # 비밀번호를 하나씩 시도합니다.
    with zipfile.ZipFile(zipfilename) as zf:
        for password in passwords:
            password = "".join(password)
            print(password)
            try:
                zf.extractall(pwd=password.encode())
                return password
            except:
                pass
    # 비밀번호를 찾지 못한 경우 None을 반환합니다.
    return None
password = crack_zip_password(r"escryption.zip", digits=True, letters=True, max_length=9)
print("비밀번호는:",password)

# %%
import requests
def currency_converter(amount, from_currency, to_currency):
# API 호출 URL
    url = f"https://api.exchangerate-api.com/v4/latest/{from_currency}"

    # API 호출 및 응답 받기
    response = requests.get(url)
    data = response.json()

    # 환율 계산
    exchange_rate = data['rates'][to_currency]
    result = round(amount * exchange_rate, 2)

    # 결과 반환
    return result
    print("환율 변환기")
print("============")

while True:
    try:
        # 변환하려는 금액 입력
       amount = float(input("변환하려는 금액을 입력하세요: "))
      
       # 변환하려는 화폐 입력
       from_currency = input("어떤 화폐에서 변환하시겠습니까? (예: USD, KRW): ").upper()
       to_currency = input("어떤 화폐로 변환하시겠습니까? (예: USD, KRW): ").upper()
       
       # 환율 계산
       result = currency_converter(amount, from_currency, to_currency)
       
       # 결과 출력
       print(f"{amount} {from_currency}은(는) {result} {to_currency}입니다.")
       
       # 계속 변환할지 묻기
       choice = input("계속 변환하시겠습니까? (Y/N): ").upper()
       if choice != "Y":
           break

    except:
        print("올바른 값을 입력해주세요.")


# %%
import zipfile
def compress_file(file_path):
    with zipfile.ZipFile(file_path + '.zip', 'w') as zip_file:
        zip_file.write(file_path)
    if __name__ == '__main__':
        compress_file('treasurehunter.txt')
# %%
import pyzipper
def compress_file_with_password(file_path, password):
    # read the file contents
    with open(file_path, 'rb') as f:
        data = f.read()
    # create a new zip file with the given name
    with pyzipper.AESZipFile(file_path + '.zip', 'w', compression=pyzipper.ZIP_DEFLATED, encryption=pyzipper.WZ_AES) as zip_file:
        # set password for the zip file
        zip_file.setpassword(password.encode('utf-8'))
        # write the file to the zip file
        zip_file.writestr(file_path, data)
if __name__ == '__main__':
    # specify the file path and password
    compress_file_with_password("treasurehunter.txt", '1234')

# %%
from googletrans import Translator
# 번역할 파일 경로
input_file_path = "Siddhartha.txt"
# 번역된 파일 저장 경로
output_file_path = "싯다르타.txt"
# 번역기 생성
translator = Translator()
# 파일 읽기
with open(input_file_path, "r", encoding="utf-8") as input_file:
    text = input_file.read()
# 번역
result = translator.translate(text, dest="ko")
# 번역된 결과를 파일에 쓰기
with open(output_file_path, "w", encoding="utf-8") as output_file:
    output_file.write(result.text)
# %%
