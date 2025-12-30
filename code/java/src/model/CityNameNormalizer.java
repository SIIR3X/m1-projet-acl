package model;

public final class CityNameNormalizer {
	public static String normalize(String name) {
        return java.text.Normalizer
                .normalize(name, java.text.Normalizer.Form.NFD)
                .replaceAll("\\p{InCombiningDiacriticalMarks}+", "")
                .toLowerCase()
                .trim();
    }
}
