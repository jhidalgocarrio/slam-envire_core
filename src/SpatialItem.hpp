#ifndef __ENVIRE_CORE_SPATIAL_ITEM__
#define __ENVIRE_CORE_SPATIAL_ITEM__

#include <envire_core/Item.hpp>
#include <envire_core/BoundingVolume.hpp>
#include <boost/intrusive_ptr.hpp>
#include <Eigen/Geometry>

namespace envire { namespace core
{

    /**@class SpatialItem
    *
    * SpatialItem class
    */
    template<class _ItemData>
    class SpatialItem : public Item<_ItemData>
    {
    protected:
        boost::intrusive_ptr<BoundingVolume> boundary;

    public:

        SpatialItem() : Item<_ItemData>()
        {

        };

        void setBoundary(const boost::intrusive_ptr<BoundingVolume>& boundary) {this->boundary = boundary;}

        boost::intrusive_ptr<BoundingVolume> getBoundary() {return boundary;}
        const boost::intrusive_ptr<BoundingVolume>& getBoundary() const {return boundary;}

        

        void extendBoundary(const Eigen::Vector3d& point)
        {
            boundary->extend(point);
        }

        template<typename _Data>
        void extendBoundary(const SpatialItem<_Data>& spatial_item)
        {
            boundary->extend(spatial_item.getBoundary());
        }

        template<typename _Data>
        bool intersects(const SpatialItem<_Data>& spatial_item) const
        {
            return boundary->intersects(spatial_item.getBoundary());
        }

        template<typename _Data>
        boost::intrusive_ptr<BoundingVolume> intersection(const SpatialItem<_Data>& spatial_item) const
        {
            return boundary->intersection(spatial_item.getBoundary());
        }

        bool contains(const Eigen::Vector3d& point) const
        {
            return boundary->contains(point);
        }

        template<typename _Data>
        bool contains(const SpatialItem<_Data>& spatial_item) const
        {
            return boundary->contains(spatial_item.getBoundary());
        }

        double exteriorDistance(const Eigen::Vector3d& point) const
        {
            return boundary->exteriorDistance(point);
        }

        template<typename _Data>
        double exteriorDistance(const SpatialItem<_Data>& spatial_item) const
        {
            return boundary->exteriorDistance(spatial_item.getBoundary());
        }

        Eigen::Vector3d centerOfBoundary() const
        {
            return boundary->center();
        }

    };

}}
#endif

