"""Various frequently used common utilities."""


import json
import logging
import os

from libmorse import exceptions, settings


RES_TEXT = "text"
RES_JSON = "json"


def get_logger(name, use_logging=settings.LOGGING, debug=settings.DEBUG):
    """Obtain a logger object given a name."""
    log = logging.getLogger(name)
    if settings.LOGFILE:
        handler = logging.FileHandler(settings.LOGFILE)
    else:
        handler = logging.StreamHandler()
    template = "%(levelname)s - %(name)s - %(asctime)s - %(message)s"
    formatter = logging.Formatter(template)
    handler.setFormatter(formatter)
    if not log.handlers:
        log.addHandler(handler)
        level = logging.DEBUG if debug else logging.INFO
        level = level if use_logging else logging.CRITICAL
        log.setLevel(level)
    return log


def get_return_code(exc):
    """Get a return code based on the raised exception."""
    if not exc:
        return 0             # all good, clean code
    if isinstance(exc, exceptions.MorseError):
        return exc.CODE      # known error, known code
    return exceptions.MorseError.CODE    # normalize to default error code


def get_resource(name, resource_type=RES_TEXT):
    """Retrieve the content of a resource name."""
    path = os.path.join(settings.RESOURCE, name)
    with open(path) as stream:
        data = stream.read()
    if resource_type == RES_TEXT:
        return data
    if resource_type == RES_JSON:
        return json.loads(data)
    raise exceptions.ProcessMorseError(
        "invalid resource type {!r}".format(resource_type))


def get_mor_code(name):
    """Get MOR code given `data`."""
    data = (get_resource(name) if isinstance(name, str)
            else name.read()).strip()
    if not data:
        return []

    mor_code = []
    for line in data.splitlines():
        # Remove extra spaces and get rig of comments.
        line = line.strip()
        idx = line.find("#")
        if idx != -1:
            line = line[:idx].strip()
        if not line:
            continue
        # Now get the status and time length of the quanta.
        chunks = line.split()
        state, duration = bool(int(chunks[0])), float(chunks[1])
        mor_code.append((state, duration))
    return mor_code


def humanize_mor_code(morse_code, unit=settings.UNIT, ratio=8.0,
                      split=False):
    """Add an expected silence at the end of the morse code."""
    length = unit * ratio
    if split:
        length /= 2
    ending = [(False, length)]
    if split:
        ending *= 2
    morse_code.extend(ending)
    return morse_code


class Logger(object):

    """Simple base class offering logging support."""

    def __init__(self, name, use_logging=settings.LOGGING,
                 debug=settings.DEBUG):
        """Log information using the `log` method.

        :param bool use_logging: enable logging or not
        :param bool debug: enable debugging messages
        """
        super(Logger, self).__init__()
        self.log = get_logger(name, use_logging=use_logging, debug=debug)

    def _log_error(self, message):
        self.log.error(str(message).strip(".!?").capitalize() + ".")
