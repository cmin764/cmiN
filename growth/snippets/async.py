import asyncio


async def waiter(event):
    print("waiting for it ...")
    await event.wait()
    print("... got it!")
    await asyncio.sleep(2)


async def run_event():
    # Create an Event object.
    event = asyncio.Event()

    # Spawn a Task to wait until 'event' is set.
    waiter_task = asyncio.create_task(waiter(event))

    # Sleep for 1 second and set the event.
    print("aaaa")
    await asyncio.sleep(1)
    event.set()

    # Wait until the waiter task is finished.
    print("bbbbb")
    await waiter_task
    print("finished")


tickets_available = 10
lock = asyncio.Lock()


async def book_ticket(user_id):
    global tickets_available

    async with lock:
        if tickets_available > 0:
            print(f"User {user_id} is booking a ticket...")
            await asyncio.sleep(1)  # Simulate processing time
            tickets_available -= 1
            print(
                f"User {user_id} successfully booked a ticket. Tickets left: {tickets_available}"
            )
        else:
            print(f"User {user_id} could not book a ticket. No tickets left.")


async def run_ticketing():
    users = [book_ticket(i) for i in range(15)]
    await asyncio.gather(*users)


asyncio.run(run_ticketing())
