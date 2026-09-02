"""Python port of the Java CrossSectionRecord contract."""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class CrossSectionRecord:
    material: str
    mf: int
    mt: int
    temperature_k: float
    interpolation: str

    def __post_init__(self) -> None:
        if not self.material or not self.material.strip():
            raise ValueError("material is required")
        if self.mf <= 0 or self.mt <= 0:
            raise ValueError("MF and MT must be positive")
        if self.temperature_k <= 0.0:
            raise ValueError("temperature must be positive")
        object.__setattr__(self, "material", self.material.strip().upper())

    def business_key(self) -> str:
        return f"{self.material}|MF={self.mf}|MT={self.mt}|T={self.temperature_k}"
