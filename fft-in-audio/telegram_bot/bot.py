import aiogram
import helper
import requests
import aiohttp
import asyncio
from datetime import datetime, timedelta
from action_sender import ChatActionSender

from aiogram import Bot, Dispatcher, executor, types
from sklearn.metrics import r2_score
import librosa
import soundfile as sf
import numpy as np
from math import cos, sin, pi
import time
from threading import Thread


BOT_TOKEN = helper.read_file('sensitive_info/bot_token')
bot = Bot(token=BOT_TOKEN)
dp = Dispatcher(bot)
sr = 12000
N = 57600
m = 4000
y, _ = librosa.load('main_audio.wav', sr=sr)
y_true = y[:N]


def get_y_hat(weights):
    print("running get_y_hat")
    y_hat = np.zeros(N)
    threads_count = 3

    def calc_y_hat(start):
        for i in range(start, start + N // threads_count):
            tmp = 2 * pi * i * np.arange(1, m + 1) / N
            y_hat[i] = (weights * np.concatenate((np.cos(tmp), -np.sin(tmp)))).sum()

    threads = []
    for j in range(threads_count):
        threads.append(Thread(target=calc_y_hat, args=[j * N // threads_count]))
    
    for t in threads:
        t.start()
    for t in threads:
        t.join()
    # for i in range(N):
    #     tmp = 2 * pi * i * np.arange(1, m + 1) / N
    #     y_hat[i] = (weights * np.concatenate((np.cos(tmp), -np.sin(tmp)))).sum()

    return y_hat


# @dp.message_handler(commands=['start', 'help'])
# async def process_help_command(message: types.Message):
#     return

users = dict()

THRESHOLD = 0.15
WAIT_TIME = 60

@dp.message_handler(content_types=types.ContentTypes.ANY)
async def any_message(message: types.Message):
    start = time.time()
    print(message)
    if "text" in dict(message).keys():
        if message.text.lower() == "never gonna give you up":
            with open("winners.txt", "a") as fout:
                fout.write(str(dict(message)))
                fout.write("\n")
            await message.reply("Вы отгадали песню!")
        else:
            await message.reply("Вы не отгадали песню, эх")
        return


    if message.from_user.id in users:
        if start - users[message.from_user.id] < WAIT_TIME:
            await message.reply("Можно делать только одну посылку в минуту.")
            return


    users[message.from_user.id] = start
    file_id = message.document.file_id
    file = await bot.get_file(file_id)
    file_path = file.file_path
    await bot.download_file(file_path, "tmp/" + message.document.file_name)
    downloading_file_time = time.time()
    print("downloading file", downloading_file_time - start)

    try:
        with open("tmp/" + message.document.file_name, 'r') as fin:
            w = np.array([float(i) for i in fin.read().split(',')])
    except:
        await message.reply("Некорректный формат вывода.")
        return
    reading_file_time = time.time()
    print("reading file", reading_file_time - downloading_file_time)
    if w.shape != (8000,):
        await message.reply("Некорретное число коэффициентов.")
        return
    y_hat = get_y_hat(w)
    score = r2_score(y_true, y_hat)
    print(score)

    sending_score_time = time.time()
    print("sending score", sending_score_time - reading_file_time)
    await message.reply(score * 100 if score > 0 else 0)
    if score > THRESHOLD:
        # librosa.output.write_wav('tmp/audio.wav', y_hat, sr)
        sf.write('tmp/audio.wav', y_hat, sr)
        await bot.send_document(message.from_user.id, open('tmp/audio.wav', 'rb'))
    with open("scores.txt", "a") as fout:
        fout.write(str(dict(message)))
        fout.write("\t")
        fout.write(str(score))
        fout.write("\n")
    sending_audio_time = time.time()
    print("sending audio", sending_audio_time - sending_score_time)


if __name__ == '__main__':
    print("started")

    executor.start_polling(dp)
