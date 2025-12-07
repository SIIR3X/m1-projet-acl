#ifndef JSON_PARSER_UTILS_H
#define JSON_PARSER_UTILS_H

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class JsonParserUtils
 * @brief Fournit des fonctions utilitaires pour parser du JSON.
 */
class JsonParserUtils
{
public:
    /**
     * @brief Extrait la valeur d'un champ JSON de type string.
     * @param json Chaîne JSON.
     * @param champ Nom du champ recherché.
     * @return La valeur du champ.
     */
    static std::string extraireChampString(const std::string& json, const std::string& champ);

    /**
     * @brief Extrait un bloc JSON associé à un champ.
     * @param json Chaîne JSON.
     * @param champ Nom du champ recherché.
     * @return Le bloc JSON.
     */
    static std::string extraireBloc(const std::string& json, const std::string& champ);

    /**
     * @brief Décompose une liste JSON en objets individuels.
     * @param bloc Chaîne contenant une liste JSON.
     * @return La liste des objets JSON.
     */
    static std::vector<std::string> extraireListeObjets(const std::string& bloc);

    /**
     * @brief Extrait un champ dans un objet JSON.
     * @param objet Objet JSON.
     * @param champ Nom du champ recherché.
     * @return La valeur du champ.
     */
    static std::string extraireChampObjet(const std::string& objet, const std::string& champ);

    /**
     * @brief Récupère un champ JSON obligatoire (depuis la racine).
     * @param json Chaîne JSON.
     * @param champ Nom du champ recherché.
     * @param extraction La fonction d'extration associée.
     * @return La valeur du champ.
     * @throws std::runtime_error si un élément requis est manquant.
     */
    static std::string recupererObligatoire(
        const std::string& json, const std::string& champ,
        std::function<std::string(const std::string&, const std::string&)> extraction);

    /**
     * @brief Récupère une liste JSON obligatoire (champ devant contenir un tableau d'objets).
     * @param json Chaîne JSON.
     * @param champ Nom du champ recherché.
     * @return La liste des objets JSON contenus dans le tableau.
     * @throws std::runtime_error si l'ensemble est manquant ou vide.
     */
    static std::vector<std::string> recupererObligatoireVecteur(const std::string& json, const std::string& champ);

private:
    /**
     * @brief Supprime les espaces au début et à la fin d'une chaîne.
     * @param s Chaîne à nettoyer.
     * @return Chaîne trimée.
     */
    static std::string _trim(const std::string& s);

    /**
     * @brief Déplace l'indice vers la prochaine position non vide.
     * @param s Chaîne source.
     * @param pos Position de départ.
     * @return Nouvelle position après les espaces.
     */
    static size_t _skipSpaces(const std::string& s, size_t pos);

    /**
     * @brief Recherche la position d'un champ JSON.
     * @param json Chaîne JSON.
     * @param champ Nom du champ recherché.
     * @return Position du champ.
     */
    static size_t _findKey(const std::string& json, const std::string& champ);

    /**
     * @brief Extrait une chaîne entre guillemets.
     * @param json Chaîne JSON.
     * @param pos Référence sur la position, avancée jusqu'à la fin de la chaîne.
     * @return Contenu de la chaîne.
     */
    static std::string _extractString(const std::string& json, size_t& pos);

    /**
     * @brief Extrait un bloc entre accolades ou crochets.
     * @param json Chaîne JSON.
     * @param pos Position du premier caractère '{' ou '['.
     * @return Le bloc JSON complet sous forme de chaîne.
     */
    static std::string _extractNumberOrLiteral(const std::string& json, size_t& pos);

    /**
     * @brief Extraint un bloc entre accolades ou crochets.
     * @param json Chaîne JSON.
     * @param pos Position du premier caractère '{' ou '['.
     * @return Le bloc JSON complet sous forme de chaîne.
     */
    static std::string _extractBracketBlock(const std::string& json, size_t pos);
};

inline std::string JsonParserUtils::extraireChampString(const std::string& json, const std::string& champ)
{
    size_t pos = _findKey(json, champ);
    if (pos == std::string::npos)
        return "";

    pos = json.find(":", pos);
    pos = _skipSpaces(json, pos + 1);

    if (json[pos] == '"')
        return _extractString(json, pos);

    return "";
}

inline std::string JsonParserUtils::extraireBloc(const std::string& json, const std::string& champ)
{
    size_t pos = _findKey(json, champ);
    if (pos == std::string::npos)
        return "";

    pos = json.find(":", pos);
    pos = _skipSpaces(json, pos + 1);

    if (json[pos] == '[' || json[pos] == '{')
        return _extractBracketBlock(json, pos);

    return "";
}

inline std::vector<std::string> JsonParserUtils::extraireListeObjets(const std::string& bloc)
{
    std::vector<std::string> res;

    size_t pos = bloc.find('[');
    if (pos == std::string::npos)
        return res;

    pos++;

    int depth = 0;

    while (pos < bloc.size())
    {
        while (pos < bloc.size() && std::isspace(static_cast<unsigned char>(bloc[pos]))) pos++;

        if (pos >= bloc.size())
            break;

        if (bloc[pos] == '{' && depth == 0)
        {
            size_t start = pos;
            int braceCount = 0;

            do
            {
                if (bloc[pos] == '{')
                    braceCount++;
                else if (bloc[pos] == '}')
                    braceCount--;
                pos++;
            } while (pos < bloc.size() && braceCount > 0);

            res.push_back(bloc.substr(start, pos - start));
            continue;
        }

        if (bloc[pos] == '[')
            depth++;
        else if (bloc[pos] == ']')
            depth--;

        pos++;
    }

    return res;
}

inline std::string JsonParserUtils::extraireChampObjet(const std::string& objet, const std::string& champ)
{
    size_t pos = _findKey(objet, champ);
    if (pos == std::string::npos)
        return "";

    pos = objet.find(":", pos);
    pos = _skipSpaces(objet, pos + 1);

    if (objet[pos] == '"')
        return _extractString(objet, pos);

    return _extractNumberOrLiteral(objet, pos);
}

inline std::string JsonParserUtils::recupererObligatoire(
    const std::string& json, const std::string& champ,
    std::function<std::string(const std::string&, const std::string&)> extraction)
{
    std::string val = extraction(json, champ);

    if (val.empty())
        throw std::runtime_error("Champ JSON obligatoire manquant : '" + champ + "'");

    return val;
}

inline std::vector<std::string> JsonParserUtils::recupererObligatoireVecteur(const std::string& json,
                                                                             const std::string& champ)
{
    std::string bloc = extraireBloc(json, champ);

    if (bloc.empty())
        throw std::runtime_error("Champ JSON obligatoire manquant ou vide : '" + champ + "'");

    std::vector<std::string> liste = extraireListeObjets(bloc);

    if (liste.empty())
        throw std::runtime_error("Le champ JSON '" + champ + "' doit contenir au moins un objet.");

    return liste;
}

inline std::string JsonParserUtils::_trim(const std::string& s)
{
    size_t begin = s.find_first_not_of(" \t\n\r");

    if (begin == std::string::npos)
        return "";

    size_t end = s.find_last_not_of(" \t\n\r");

    return s.substr(begin, end - begin + 1);
}

inline size_t JsonParserUtils::_skipSpaces(const std::string& s, size_t pos)
{
    while (pos < s.size() && std::isspace(s[pos])) pos++;

    return pos;
}

inline size_t JsonParserUtils::_findKey(const std::string& json, const std::string& champ)
{
    std::string key = "\"" + champ + "\"";
    return json.find(key);
}

inline std::string JsonParserUtils::_extractString(const std::string& json, size_t& pos)
{
    size_t start = ++pos;
    size_t end = json.find('"', start);
    pos = end + 1;
    return json.substr(start, end - start);
}

inline std::string JsonParserUtils::_extractNumberOrLiteral(const std::string& json, size_t& pos)
{
    size_t start = pos;

    while (pos < json.size() && json[pos] != ',' && json[pos] != '}' && json[pos] != ']') pos++;

    return _trim(json.substr(start, pos - start));
}

inline std::string JsonParserUtils::_extractBracketBlock(const std::string& json, size_t pos)
{
    char open = json[pos];
    char close = (open == '[' ? ']' : '}');

    int count = 0;
    size_t start = pos;

    for (; pos < json.size(); ++pos)
    {
        if (json[pos] == open)
            count++;
        else if (json[pos] == close)
            count--;

        if (count == 0)
            break;
    }

    return json.substr(start, pos - start + 1);
}

#endif  // JSON_PARSER_UTILS_H