FROM python:3.8-slim-buster

WORKDIR /wise-app

COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt
ENV PORT 80

COPY . .

CMD [ "python3", "app.py"]
