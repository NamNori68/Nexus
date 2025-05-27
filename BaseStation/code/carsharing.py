from fastapi.responses import JSONResponse
import uvicorn

from fastapi import FastAPI, Request
from contextlib import asynccontextmanager
from sqlmodel import SQLModel
from routers import cars, web, auth
from db import engine


@asynccontextmanager
async def lifespan(app: FastAPI):
    SQLModel.metadata.create_all(engine)
    yield

app = FastAPI(title="Car Sharing", lifespan=lifespan)
app.include_router(cars.router)
app.include_router(web.router)
app.include_router(auth.router)
