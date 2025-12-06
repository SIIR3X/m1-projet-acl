#ifndef I_DATA_BUILDER_H
#define I_DATA_BUILDER_H

/**
 * @class IDataBuilder
 * @brief Interface statique générique pour les DataBuilders (pattern CRTP).
 */
template <typename Derivee>
class IDataBuilder
{
public:
    /**
     * @brief Appelle la méthode statique "construireData" implémentée dans la classe dérivée.
     * @tparam Args Types des objets reçus.
     * @param args Objets passés au builder.
     */
    template <typename... Args>
    static auto construireDonnees(Args&&... args)
    {
        return Derivee::construireDonnees(std::forward<Args>(args)...);
    }
};

#endif  // I_DATA_BUILDER_H