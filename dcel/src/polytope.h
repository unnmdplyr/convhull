

#ifndef POLYTOPE_H_
#define POLYTOPE_H_

#include <memory>
#include <vector>
#include "types.h"
#include "iterator.h"


namespace ch
{

	class polytope final
	{
	public:
		polytope();

		///	\return	With true if the face already existed. Otherwise false.
		bool addFace( const std::vector<vid_t>& vertices );
		///	\return	With true if the face existed and false if not.
		bool removeFace( fid_t fid );
		///	\return	With true if the faces merged. Otherwise with false.
		bool mergeFaces( fid_t fid1, fid_t fid2 );

		std::unique_ptr< iterator<fid_t > > createFaceIterator() 					const;
		std::unique_ptr< iterator<heid_t> > createHalfEdgeIterator	(fid_t faceId)	const;
		std::unique_ptr< iterator<vid_t > > createVertexIterator	(fid_t faceId)	const;
		std::unique_ptr< iterator<heid_t> > createHalfEdgesAroundVertexIterator(vid_t vertexId) const;

		polytope( const polytope& rhs ) = delete;
		polytope& operator=( const polytope& rhs ) = delete;

	private:
		vertex_t	vertices;
		half_edge_t	half_edges;
		face_t		faces;

		fid_t		faceIdCounter;

		//	Accelearator objects in the class for avoiding constant object creation and deletion
		mutable vertex		accVertex;
		mutable half_edge	accHalfEdge;
		mutable face		accFace;

		//----------------------------------------------------------------------
		//	Iterators
		//----------------------------------------------------------------------
		//	Face id
		class face_iterator : public iterator<fid_t>
		{
		public:
			face_iterator( const face_t& faceColl );
			virtual void first();
			virtual void next();
			virtual bool done();
			virtual const fid_t& current() const;
		private:
			face_t::iterator	faceIt;
			const face_t& faceCollection;
		};

		//	Half Edge id
		class half_edge_iterator : public iterator<heid_t>
		{
		public:
			half_edge_iterator	( heid_t first, const half_edge_t& halfEdgeColl );
			virtual void first();
			virtual void next();
			virtual bool done();
			virtual const heid_t& current() const;
		private:
			heid_t firstHalfEdge;
			heid_t currentHalfEdge;
			const half_edge_t& halfEdgeCollection;
			///	Indicates whether the first half edge already left during the
			///	iteration. Or the iterator is still at the first he and the
			///	function next() has been not yet called.
			size_t firstHeLeft;
		};

		//	Vertex id
		class vertex_iterator : public iterator<vid_t>
		{
		public:
			vertex_iterator		( std::unique_ptr< iterator<heid_t> >&& halfEdgeIterator );
			virtual void first();
			virtual void next();
			virtual bool done();
			virtual const vid_t& current() const;
		private:
			std::unique_ptr< iterator<heid_t> > heit;
		};

		//	Half edges around vertex
		class half_edges_around_vertex_iterator : public iterator<heid_t>
		{
		public:
			half_edges_around_vertex_iterator( heid_t first, const half_edge_t& halfEdgeColl );
			virtual void first();
			virtual void next();
			virtual bool done();
			virtual const heid_t& current() const;
		private:
			bool twinHalfEdgeExists( const heid_t heid ) const;
			heid_t firstHalfEdge;
			heid_t currentHalfEdge;
			const half_edge_t& halfEdgeCollection;
			size_t firstHeLeft;
			size_t leftSideEnd;
			size_t rightSideEnd;
		};

		//----------------------------------------------------------------------
		//----------------------------------------------------------------------

	private:
		size_t vertexNumber() const;
		size_t halfEdgeNumber() const;
		size_t faceNumber() const;

		bool vertexExists( const vid_t vid ) const;

		bool halfEdgeExists( const vid_t firstVertexId, const vid_t secondVertexId ) const;
		bool halfEdgeExists( const heid_t heid ) const;
		bool halfEdgeExists( heid_t heid, half_edge& he ) const;
		void getHalfEdge( heid_t heid, half_edge& he ) const;
		void removeHalfEdge( heid_t heid );

		void replaceHalfEdgeNext( heid_t toBeReplaceHeId, heid_t replaceWithHeId );
		void replaceHalfEdgePrev( heid_t toBeReplaceHeId, heid_t replaceWithHeId );
		void replaceHalfEdge(	heid_t toBeReplaceHeId, heid_t replaceWithHeId,
								void (polytope::*modifier)(half_edge&, heid_t) );
		void halfEdgeModifierNext( half_edge& he, heid_t nextVal );
		void halfEdgeModifierPrev( half_edge& he, heid_t prevVal );

		bool twinHalfEdgeExists( const heid_t heid ) const;
		bool twinHalfEdgeExists( const heid_t heid, half_edge& he ) const;
		heid_t getTwinHalfEdgeId( const heid_t heid ) const;

		bool faceExists	( const std::vector<vid_t>& vertIds ) const;
		bool faceExists	( const fid_t faceId ) const;
		bool faceExists	( const fid_t faceId, face& face ) const;
		void getFace	( const fid_t faceId, face& face ) const;
		bool areFacesAdjacent( fid_t fid1, fid_t fid2, heid_t& he ) const;

		fid_t	getNextFaceId();
		void addVertexAndIncidentEdge( 	vid_t vertId, heid_t&& incidentEdgeId,
										heid_t&& prevHeId, heid_t&& nextHeId,
										fid_t faceId );
	};

}

#endif /* POLYTOPE_H_ */
