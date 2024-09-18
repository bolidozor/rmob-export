# Použijeme základní image s Pythonem
FROM python:3.12-slim

# Nainstalujeme cron
RUN apt-get update && apt-get install -y \
    cron \
    coreutils \
    libcairo2 \
    libcairo2-dev \
    libpango1.0-0 \
    libpangocairo-1.0-0 \
    libgdk-pixbuf2.0-0 \
    libffi-dev \
    libjpeg-dev \
    libpng-dev \
    libxml2-dev \
    libxslt1-dev \
    zlib1g-dev

# Vytvoříme pracovní adresář
WORKDIR /app

# Zkopírujeme Python skript do kontejneru
COPY ./src /app

COPY requirements.txt /app/requirements.txt
RUN pip install --no-cache-dir -r /app/requirements.txt --break-system-packages

CMD python3 multigen.py
