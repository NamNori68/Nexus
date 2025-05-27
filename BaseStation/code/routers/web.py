from fastapi import APIRouter, Request, Form, Depends, Cookie
from fastapi.responses import HTMLResponse
from fastapi.templating import Jinja2Templates
from typing import Annotated


from sqlmodel import Session

from db import get_session
from routers.cars import get_cars

router = APIRouter()

templates = Jinja2Templates(directory="templates")

@router.get("/", response_class=HTMLResponse)
def home(Request: Request):
    return templates.TemplateResponse("home.html", {"request": Request})

@router.post("/search", response_class=HTMLResponse)
def search(size: Annotated[str, Form()],
           doors: Annotated[int, Form()],
           request: Request,
           session: Annotated[Session, Depends(get_session)]):
    cars = get_cars(size=size, doors=doors, sesison=session)
    return templates.TemplateResponse("search_results.html", 
                                      {"request": request, "cars": cars})
