package io.data;

public record RouteKey(String from, String to) 
{

    public RouteKey 
    {
        from = normalize(from);
        to = normalize(to);
    }

    private static String normalize(String s) 
    {
        return s.toLowerCase()
                .replace("é", "e")
                .replace("è", "e")
                .replace("ê", "e")
                .replace("à", "a")
                .replace("ù", "u")
                .replace("ô", "o")
                .trim();
    }
}