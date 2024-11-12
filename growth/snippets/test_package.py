from contextlib import nullcontext as does_not_raise

import pytest
from pydantic import ValidationError

# Assuming the script is named package.py.
from package import Package, Stack, classify_package


@pytest.mark.parametrize(
    "width, height, length, mass, expectation, expected_classification",
    [
        # Sweet case: dimensions and mass are below thresholds.
        (50.0, 40.0, 30.0, 10.0, does_not_raise(), Stack.STANDARD),
        # Case with a dimension and mass exceeding the thresholds.
        (160.0, 40.0, 30.0, 25.0, does_not_raise(), Stack.REJECTED),
        # Case where dimensions and mass are below limits, but volume exceeds threshold.
        (100.0, 100.0, 100.0, 10.0, does_not_raise(), Stack.SPECIAL),
        # Invalid data case: negative dimension.
        (-10.0, 20.0, 30.0, 15.0, pytest.raises(ValidationError), None),
        # Invalid data case: zero mass.
        (1.0, 40.0, 30.0, 0.0, pytest.raises(ValidationError), None),
    ],
)
def test_classify_package(
    width, height, length, mass, expectation, expected_classification
):
    """Test `classify_package` with various cases."""
    with expectation:
        package = Package(width=width, height=height, length=length, mass=mass)

    # Early exit if an error is expected to be already handled above.
    if expected_classification is None:
        return

    # Otherwise, check the classification
    classification = classify_package(package)
    assert classification is expected_classification
