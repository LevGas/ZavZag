/*
	File: 
		zz_request.h
	Abstract:
		Defines the all supported request classes
*/

#ifndef ZZ_REQUEST_H
#define ZZ_REQUEST_H

////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#ifndef ZZ_CORE_H
#	include "zz_core.h"
#endif

//	Qt includes

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace zz { //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//	class CRequest
//!	Base class for all request types
class ZZ_CORE_EXPORT CRequest
{
public:
	// Request data definition
	typedef QHash<QString, QVariant> t_RequestData;

public:
	//! Default Constructor
	inline CRequest( ERequestType eType = ERequestType::Undefined );
	//! Construct from the byte data
	//! Data buffer should contain only the data part (without header)
	inline CRequest( ERequestType eType, QByteArray& aDataBuffer );
	//! Destructor
	virtual ~CRequest();

public:
	//
	//	Main Interface
	//
	// Returns request type
	inline ERequestType   getType() const;
	// Returns request status
	// inline ERequestStatus getRequestStatus() const;
	// Checks request validation
	inline bool isValid() const;
	// Add data item
	inline void addItem( QString const& sKey, QVariant const& vtValue );
	// Remove data item
	inline void removeItem( QString const& sKey );
	// Get item Count
	inline int  getItemCount() const;
	// Is there any items 
	inline bool isEmpty();
	// Get value of data item
	inline QVariant getValue( QString const& sKey ) const;
	// Returns all item keys
	inline QStringList getAllKeys() const;
	// Returns all item values
	inline QList<QVariant> getAllValues() const;

	// Serializes and returns data buffer which is ready to be transmitted
	QByteArray serialize() const;

private:
	//
	//	Content
	//
	ERequestType   m_eType;
	t_RequestData  m_hshData;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	Inline Implementations
//
////////////////////////////////////////////////////////////////////////////////

//! Constructor
inline CRequest::CRequest( ERequestType eType )
	: m_eType(eType)
{}

//! Constructor
inline CRequest::CRequest( ERequestType eType, QByteArray& aDataBuffer )
	: m_eType( isValidRequest(eType)? eType : ERequestType::Undefined )
{
	QDataStream oIn( &aDataBuffer, QIODevice::ReadOnly );
	oIn >> m_hshData;
}

// getType
inline ERequestType CRequest::getType() const { return m_eType; }
// isValid
inline bool CRequest::isValid() const { return isValidRequest( m_eType ); }

// addItem
inline void CRequest::addItem( QString const& sKey, QVariant const& vtValue )
{
	m_hshData.insert(sKey, vtValue);
}
// removeItem
inline void CRequest::removeItem( QString const& sKey )
{
	m_hshData.remove( sKey );
}
// getValue
inline QVariant CRequest::getValue( QString const& sKey ) const
{
	return m_hshData.value( sKey );
}
// getItemCount
inline int  CRequest::getItemCount() const
{
	return m_hshData.size();
}
// isEmpty
inline bool CRequest::isEmpty()
{
	return m_hshData.isEmpty();
}
// getAllKeys
inline QStringList CRequest::getAllKeys() const
{
	return m_hshData.keys();
}
// getAllValues
inline QList<QVariant> CRequest::getAllValues() const
{
	return m_hshData.values();
}


////////////////////////////////////////////////////////////////////////////////
} // namespace zz
////////////////////////////////////////////////////////////////////////////////

#endif // ZZ_REQUEST_H
/* end of file */
