import os

from dotenv import load_dotenv
from telethon.sync import TelegramClient
from telethon.tl.functions.channels import GetParticipantsRequest
from telethon.tl.types import ChannelParticipantsSearch

# Load environment variables
load_dotenv()
api_id = os.getenv("TELEGRAM_API_ID")
api_hash = os.getenv("TELEGRAM_API_HASH")
group_username = ""

# Log in to Telegram
client = TelegramClient("session_name", api_id, api_hash)
client.start()


participants = client(
    GetParticipantsRequest(
        group_username,
        ChannelParticipantsSearch(""),
        0,
        100,
        hash=0,  # Use 0 for the hash parameter
    )
).users

# Export participant details
with open("group_members.csv", "w") as file:
    file.write("Username,UserID\n")
    for user in participants:
        username = user.username if user.username else ""
        user_id = user.id
        file.write(f"{username},{user_id}\n")

client.disconnect()
