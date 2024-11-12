#! /usr/bin/env python

from enum import Enum
from typing import Annotated

import typer
from pydantic import BaseModel, ValidationError, confloat, Field

# Constants for package classification.
VOLUME_THRESHOLD = 1_000_000.0  # volume threshold in cm³
DIMENSION_THRESHOLD = 150.0  # dimension threshold in cm
MAX_WEIGHT = 20.0  # weight limit in kg

app = typer.Typer()


class Stack(Enum):
    """Classification stack for package handling."""

    STANDARD = "STANDARD"  # standard handling
    SPECIAL = "SPECIAL"  # requires special handling due to bulkiness or weight
    REJECTED = "REJECTED"  # cannot be handled due to excessive bulk and weight


class Package(BaseModel):
    """Model for validating and representing a package's dimensions and mass."""

    width: Annotated[
        confloat(gt=0.0),
        Field(description="Width of the package in cm (must be > 0.0)"),
    ]
    height: Annotated[
        confloat(gt=0.0),
        Field(description="Height of the package in cm (must be > 0.0)"),
    ]
    length: Annotated[
        confloat(gt=0.0),
        Field(description="Length of the package in cm (must be > 0.0)"),
    ]
    mass: Annotated[
        confloat(gt=0.0),
        # Since I don't believe is worth delivering photons.
        Field(description="Mass of the package in kg (must be > 0.0)"),
    ]


def classify_package(package: Package) -> Stack:
    """Classifies a package based on its dimensions and mass.

    A package is considered:
    - REJECTED if it is both bulky (volume >= 1,000,000 cm³ or any dimension >= 150 cm)
    and heavy (mass >= 20 kg).
    - SPECIAL if it is either bulky or heavy.
    - STANDARD if it is neither bulky nor heavy.

    Args:
        package: The package to classify.

    Returns:
        Stack: The classification of the package as STANDARD, SPECIAL, or REJECTED.
    """
    volume = package.width * package.height * package.length
    is_bulky = volume >= VOLUME_THRESHOLD or any(
        dim >= DIMENSION_THRESHOLD
        for dim in (package.width, package.height, package.length)
    )
    is_heavy = package.mass >= MAX_WEIGHT

    if is_heavy and is_bulky:
        return Stack.REJECTED
    elif is_heavy or is_bulky:
        return Stack.SPECIAL
    return Stack.STANDARD


@app.command()
def main(width: float, height: float, length: float, mass: float):
    """Main CLI command to classify a package based on user input.

    Takes package dimensions and mass from CLI arguments, validates them, and
    classifies the package as STANDARD, SPECIAL or REJECTED.

    Args:
        width: Width of the package in cm.
        height: Height of the package in cm.
        length: Length of the package in cm.
        mass: Mass of the package in kg.
    """
    try:
        # Package's characteristics are validated during the package creation.
        package = Package(width=width, height=height, length=length, mass=mass)
        classification = classify_package(package)
        typer.echo(f"The package is classified as: {classification.value}")
    except ValidationError as exc:
        typer.echo("Invalid package data:")
        typer.echo(exc.json())


if __name__ == "__main__":
    app()
