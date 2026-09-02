package nea.demo;

import java.util.Locale;
import java.util.Objects;

/**
 * Tiny legacy-style domain object.
 * Interview artefact — not part of JANIS.
 */
public final class CrossSectionRecord {
    private final String material;
    private final int mf;
    private final int mt;
    private final double temperatureK;
    private final String interpolation;

    public CrossSectionRecord(String material, int mf, int mt,
                              double temperatureK, String interpolation) {
        if (material == null || material.trim().isEmpty()) {
            throw new IllegalArgumentException("material is required");
        }
        if (mf <= 0 || mt <= 0) {
            throw new IllegalArgumentException("MF and MT must be positive");
        }
        if (temperatureK <= 0.0) {
            throw new IllegalArgumentException("temperature must be positive");
        }
        this.material = material.trim().toUpperCase(Locale.ROOT);
        this.mf = mf;
        this.mt = mt;
        this.temperatureK = temperatureK;
        this.interpolation = Objects.requireNonNull(interpolation);
    }

    public String businessKey() {
        return material + "|MF=" + mf + "|MT=" + mt + "|T=" + temperatureK;
    }

    public String getMaterial() { return material; }
    public int getMf() { return mf; }
    public int getMt() { return mt; }
    public double getTemperatureK() { return temperatureK; }
    public String getInterpolation() { return interpolation; }
}
