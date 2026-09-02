FROM python:3.12-slim AS runtime
WORKDIR /opt/app
ENV PYTHONDONTWRITEBYTECODE=1 PYTHONUNBUFFERED=1
COPY 02-python-pipelines/pipeline /opt/app/pipeline
WORKDIR /opt/app/pipeline
CMD ["python3", "endf_ingest.py"]
